#include "lbf.h"

#include <iostream>
#include <Windows.h>

#include "align.h"
#include "filter.h"
#include "timer.h"

namespace lbf {
#pragma region Assert

#undef assert
#ifdef ENABLE_ASSERT
    static void _pwassert(const wchar_t* expression, const wchar_t* file, unsigned line)
    {
        printf("PW Assertion failed: %ws\n%ws(%u)\n", expression, file, line);
        volatile int i = 0;
        i = 1 / i;
    }
#define assert(expr) (void)((!!(expr)) || (_pwassert(_CRT_WIDE(#expr), _CRT_WIDE(__FILE__), (unsigned)(__LINE__)), 0))
#else
#define assert(expr) ((void)(0))
#endif

    /**
    !!!DO NOT use it like "if(condition) check_error(expr, ret); else{...}"
    !!!USE "if(condition){check_error(expr, ret);} else{...}" instead
    */
#define check_error(expr, ret) if(!(expr)) return -(ret)

#pragma endregion

#pragma region Cascade

    const static std::string _CLI_TEST_PATH_PREFIX = "./res/test/";

    /* Detect cascade */
    const static std::string _CLI_DETECT_CASCADE_PATH = "./res/haarcascade/haarcascade_frontalface_alt2.xml";
    const static int _MAX_REJECT_LV = 20;//corresponding to xml
    static cv::CascadeClassifier _cc;
    static bool _haarCascadeloaded = false;
    /* Detect cascade */

    /* Align cascade */
    const static std::string _CLI_ALIGN_CASCADE_PATH = "./res/model/model_loose.bin";
    static Align* _align = nullptr;
    /* Align cascade */

#pragma endregion

#pragma region Structure

    /** EYE_[which eye]_[position]
    [which eye]: LEFT means left eye, RIGHT means right eye
    [position]: from camera to the face(meaning left eye is on the right)
    */
    using EYE_SHAPE_IDX = enum
    {
        EYE_LEFT_RIGHT = 27,
        EYE_LEFT_TOP = 28,
        EYE_LEFT_LEFT = 29,
        EYE_LEFT_BOTTOM = 30,
        EYE_RIGHT_LEFT = 31,
        EYE_RIGHT_TOP = 32,
        EYE_RIGHT_RIGHT = 33,
        EYE_RIGHT_BOTTOM = 34,
        EYE_LEFT_UPRIGHT = 65,
        EYE_LEFT_DOWNRIGHT = 66,
        EYE_LEFT_DOWNLEFT = 67,
        EYE_LEFT_UPLEFT = 68,
        EYE_RIGHT_UPRIGHT = 69,
        EYE_RIGHT_DOWNRIGHT = 70,
        EYE_RIGHT_DOWNLEFT = 71,
        EYE_RIGHT_UPLEFT = 72,
        EYE_LEFT_CENTER = 73,
        EYE_RIGHT_CENTER = 74,
    };

    class Eye
    {
    public:
        double2 l, r;
        double2 top, bottom;
        double2 ul, ur, dl, dr;
        double2 center;

        Eye() {}
        Eye(
            double2 _l, double2 _r, double2 _t, double2 _b,
            double2 _ul, double2 _ur, double2 _dl, double2 _dr,
            double2 _center
        )
        {
            set(_l, _r, _t, _b, _ul, _ur, _dl, _dr, _center);
        }

        void set(
            double2 _l, double2 _r, double2 _t, double2 _b,
            double2 _ul, double2 _ur, double2 _dl, double2 _dr,
            double2 _center
        );
    private:
        bool normalized = false;
        /* 10px wide, relative position of center */
        void normalize();
    };

    class Eyes
    {
    public:
        Eye left;
        Eye right;

        Eyes(const std::vector<double2>& shape)
        {
            this->left = Eye(
                shape[EYE_LEFT_LEFT],
                shape[EYE_LEFT_RIGHT],
                shape[EYE_LEFT_TOP],
                shape[EYE_LEFT_BOTTOM],
                shape[EYE_LEFT_UPLEFT],
                shape[EYE_LEFT_UPRIGHT],
                shape[EYE_LEFT_DOWNLEFT],
                shape[EYE_LEFT_DOWNRIGHT],
                shape[EYE_LEFT_CENTER]
            );
            this->right = Eye(
                shape[EYE_RIGHT_LEFT],
                shape[EYE_RIGHT_RIGHT],
                shape[EYE_RIGHT_TOP],
                shape[EYE_RIGHT_BOTTOM],
                shape[EYE_RIGHT_UPLEFT],
                shape[EYE_RIGHT_UPRIGHT],
                shape[EYE_RIGHT_DOWNLEFT],
                shape[EYE_RIGHT_DOWNRIGHT],
                shape[EYE_RIGHT_CENTER]
            );
        }
    };

#pragma endregion

#pragma region PrivateAPI

#pragma region Utils

    static double lookAtRot(double2 src, double2 tgt);

#pragma endregion

#pragma region Face

    /* With the highest level and the largest weight */
    static void faceFilter(const cv::Mat& image, std::vector<cv::Rect>& faces, std::vector<int>& rejLvs, std::vector<double>& rejWs);
    static void faceDetect(const cv::Mat& image, const cv::Mat& image_flip, std::vector<cv::Rect>& faces);

#pragma endregion

#pragma endregion

#pragma region PublicAPI
    bool loadHaarCascade()
    {
        return loadHaarCascade(_CLI_DETECT_CASCADE_PATH);
    }

    bool loadHaarCascade(const std::string& cascadePath)
    {
        if (!_haarCascadeloaded && _cc.load(cascadePath))
        {
            _haarCascadeloaded = true;
            return true;
        }
        return _haarCascadeloaded;
    }

    void unloadHaarCascade()
    {
        _haarCascadeloaded = false;
    }

    bool isHaarLoaded()
    {
        return _haarCascadeloaded;
    }

    bool loadAlignCascade()
    {
        return loadAlignCascade(_CLI_ALIGN_CASCADE_PATH);
    }

    bool loadAlignCascade(const std::string& cascadeName)
    {
        if (!_align)
        {
            mytic();
            _align = new Align(cascadeName);
            mytoc("model loading time");
            if (!_align->IsLoaded())
            {
                delete _align;
                _align = nullptr;
                return false;
            }
        }
        return true;
    }

    void unloadAlignCascade()
    {
        if (_align)
        {
            delete _align;
            _align = nullptr;
        }
    }

    bool isAlignLoaded()
    {
        return !(_align == nullptr);
    }

    int alignImage(const std::string imgPath, cv::Mat& outImage, std::vector<double2>& outShape)
    {
        check_error(_haarCascadeloaded, LBF_ERR_NO_HAAR);
        check_error(_align, LBF_ERR_NO_ALIGN);
        outImage = cv::imread(imgPath);
        check_error(outImage.rows != 0, LBF_ERR_IO_FAIL);

        return alignImage(outImage, outShape);
    }

    int alignImage(const cv::Mat& image, std::vector<double2>& outShape)
    {
        check_error(_haarCascadeloaded, LBF_ERR_NO_HAAR);
        check_error(_align, LBF_ERR_NO_ALIGN);
        check_error(image.rows != 0, LBF_ERR_IO_FAIL);
        outShape.clear();
        // using grayscale image and flip, add paddings
        cv::Mat imageGray;
        cv::Mat imageGrayFlip;
        cvtColor(image, imageGray, CV_BGR2GRAY);
        int rowPadding = image.rows / 4;
        int colPadding = image.cols / 4;
        cv::copyMakeBorder(imageGray, imageGray, rowPadding, rowPadding, colPadding, colPadding, cv::BORDER_CONSTANT, cv::Scalar(0, 0, 0));
        equalizeHist(imageGray, imageGray);
        flip(imageGray, imageGrayFlip, 1);

        std::vector<cv::Rect> faces;
        faceDetect(imageGray, imageGrayFlip, faces);

        mytic();
        cv::Mat shape;
        if (!faces.empty())
        {
            cv::Rect* r = &faces[0];
            cv::Vec4d bb(r->x + r->width / 2, r->y + r->height / 2, r->width / 2, r->height / 2);
            lbf_log("bb %f, %f, %f, %f", r->x + r->width / 2, r->y + r->height / 2, r->width / 2, r->height / 2);
            shape = _align->predict(imageGray, bb);
        }
        mytoc("align time");
        /* remove paddings */
        for (int i = 0; i < shape.rows; i++)
        {
            outShape.emplace_back(shape.at<cv::Vec2d>(i)[0] - colPadding, shape.at<cv::Vec2d>(i)[1] - rowPadding);
        }
        return LBF_ERR_SUCC;
    }

    int alignVideo(const std::string videoPath, CvCapture*& outFrames, std::vector<std::vector<double2>>& outShapes)
    {
        cvReleaseCapture(&outFrames);
        outShapes.clear();
        check_error(_haarCascadeloaded, LBF_ERR_NO_HAAR);
        check_error(_align, LBF_ERR_NO_ALIGN);
        outFrames = cvCreateFileCapture(videoPath.c_str());
        check_error(outFrames, LBF_ERR_IO_FAIL);

        return alignVideo(outFrames, outShapes);
    }

    int alignVideo(CvCapture* const& frames, std::vector<std::vector<double2>>& outShapes)
    {
        outShapes.clear();
        check_error(_haarCascadeloaded, LBF_ERR_NO_HAAR);
        check_error(_align, LBF_ERR_NO_ALIGN);
        check_error(frames, LBF_ERR_IO_FAIL);

        mytic();
        int cnt = 0;
        /* Capture frames */
        for (;;)
        {
            lbf_log("frame %d\n", cnt);
            IplImage* iplImg = cvQueryFrame(frames);
            cv::Mat image = cv::cvarrToMat(iplImg);
            if (image.empty())
                break;
            if (iplImg->origin != IPL_ORIGIN_TL)
                flip(image, image, 0);

            std::vector<double2> shape;
            alignImage(image, shape);
            outShapes.push_back(shape);
#ifdef DUMP_FRAME
            char imgname[128];
            sprintf(imgname, "test/frame%04d.png", cnt);
            imwrite(imgname, image);
#endif
            cnt++;
        }
        mytoc("capture time");
        cvSetCaptureProperty(frames, CV_CAP_PROP_POS_FRAMES, 0);
        return LBF_ERR_SUCC;
    }

    void getEyeDataFromShapes(const std::vector<std::vector<double2>>& shapes, std::vector<double>& outLEye, std::vector<double>& outREye)
    {
        std::vector<double> l[2], r[2];
        for (size_t i = 0; i < shapes.size(); i++)
        {
            /* Has no faces */
            if (shapes[i].empty())
            {
                l[0].push_back(-10);
                r[0].push_back(-10);
            }
            /* Has a face */
            else
            {
                Eyes eyes(shapes[i]);
                l[0].push_back(eyes.left.bottom.y - eyes.left.top.y);
                r[0].push_back(eyes.right.bottom.y - eyes.right.top.y);
            }
        }
        /* Filter */
        for (int i = 0; i < 5; i++)
        {
            pw::filterExp1Point5(l[i % 2], l[1 - i % 2]);
            pw::filterExp1Point5(r[i % 2], r[1 - i % 2]);
        }
#ifdef DUMP_SHAPE
        FILE* fp = NULL;
        fopen_s(&fp, "test/eye_data.csv", "w");
        for (int i = 0; i < l[1].size(); i++)
        {
            fprintf(fp, "F%04d, %2.4f, %2.4f\n", i, l[1][i], r[1][i]);
            fflush(fp);
        }
        fclose(fp);
#endif
        outLEye = std::move(l[1]);
        outREye = std::move(r[1]);
    }

    void getEyeDataFromFile(const std::string & shapesPath, std::vector<double>& outLEye, std::vector<double>& outREye)
    {
        outLEye.clear();
        outREye.clear();
        FILE* fp = NULL;
        fopen_s(&fp, shapesPath.c_str(), "r");
        int i;
        double ll, rr;
        while (fscanf(fp, "F%d, %lf, %lf\n", &i, &ll, &rr) > 0)
        {
            outLEye.push_back(ll);
            outREye.push_back(rr);
        }
        fclose(fp);
    }

    void getTickFromData(const std::vector<double>& eyeData, int & outCnt)
    {
        const double CLOSE_THRESHOLD = 1.0;// Above means opened, below means closed
        const int TIME_OUT = 60;// if eye closed for too long, then means it's closed, not blinking

        outCnt = 0;// total ticks

        /* blink means negedge followed by a posedge */
        bool isOpenPrev = true;
        bool isOpen = true;
        bool ticking = false;
        /* blink means negedge followed by a posedge */

        size_t startBlinkingTime = 0;// record negedge's time
        size_t lastBlinkTime = 0;// last blink, 0 if current is the first
        size_t blinkTime = 0;// current blink
        size_t interval = 0;// (current - last), do not calculate if last is 0

        for (size_t i = 0; i < eyeData.size(); i++)
        {
            isOpenPrev = isOpen;
            isOpen = eyeData[i] > CLOSE_THRESHOLD;
            if (isOpenPrev && !isOpen)
            {
                ticking = true;
                startBlinkingTime = i;
            }
            else if (!isOpenPrev && isOpen && ticking)
            {
                /* Blink */
                if (i - startBlinkingTime <= TIME_OUT)
                {
                    lastBlinkTime = blinkTime;
                    blinkTime = (i + startBlinkingTime) >> 1;
                    if (lastBlinkTime != 0)
                    {
                        interval = (interval * 7 + (blinkTime - lastBlinkTime)) / 8;
                    }
                    ++outCnt;
                }
                /* eye closed */
                else
                {
                    lastBlinkTime = 0;
                    blinkTime = 0;
                }
                ticking = false;
            }
        }
    }

#pragma endregion
}

int main(int argc, char* argv[])
{
    lbf::loadHaarCascade();
    CvCapture *capture = nullptr;
    capture = cvCreateFileCapture("D:\\ptosis\\test_ptosis\\83-caoyuxuan\\2\\IMG_5419.MOV");
    check_error(capture, lbf::LBF_ERR_IO_FAIL);

    mytic();
    int cnt = 0;
    /* Capture frames */
    for (;;)
    {
        lbf_log("frame %d\n", cnt);
        IplImage* iplImg = cvQueryFrame(capture);
        cv::Mat image = cv::cvarrToMat(iplImg);
        if (image.empty())
            break;
        if (iplImg->origin != IPL_ORIGIN_TL)
            flip(image, image, 0);

        check_error(lbf::_haarCascadeloaded, lbf::LBF_ERR_NO_HAAR);
        // using grayscale image and flip, add paddings
        cv::Mat imageGray;
        cv::Mat imageGrayFlip;
        cvtColor(image, imageGray, CV_BGR2GRAY);
        int rowPadding = image.rows / 4;
        int colPadding = image.cols / 4;
        cv::copyMakeBorder(imageGray, imageGray, rowPadding, rowPadding, colPadding, colPadding, cv::BORDER_CONSTANT, cv::Scalar(0, 0, 0));
        equalizeHist(imageGray, imageGray);
        flip(imageGray, imageGrayFlip, 1);
        std::vector<cv::Rect> faces;
        std::vector<int> rejectLv;
        std::vector<double> rejectW;
        lbf::faceDetect(imageGray, imageGrayFlip, faces);

        mytic();
        for (auto &face : faces)
        {
            cv::circle(image, cv::Point(face.x - colPadding + face.width / 2, face.y - rowPadding + face.height / 2), face.width / 2, cv::Scalar(255, 0, 0));
        }
        mytoc("align time");
        cv::imshow("ex", image);
        cvWaitKey(33);
        cnt++;
    }
    mytoc("capture time");
    cvReleaseCapture(&capture);
    return lbf::LBF_ERR_SUCC;
}

void lbf::Eye::set(double2 _l, double2 _r, double2 _t, double2 _b, double2 _ul, double2 _ur, double2 _dl, double2 _dr, double2 _center)
{
    center = _center;
    l = _l - center;
    r = _r - center;
    top = _t - center;
    bottom = _b - center;
    ul = _ul - center;
    ur = _ur - center;
    dl = _dl - center;
    dr = _dr - center;
    normalize();
}

void lbf::Eye::normalize()
{
    if (normalized)
        return;
    double rot = lookAtRot(l, r);
    //rotate
    double2 tmp;
    double costheta = cos(rot);
    double sintheta = sin(rot);
    tmp.x = costheta * l.x + sintheta * l.y;
    tmp.y = -sintheta * l.x + costheta * l.y;
    l = tmp;
    tmp.x = costheta * r.x + sintheta * r.y;
    tmp.y = -sintheta * r.x + costheta * r.y;
    r = tmp;
    tmp.x = costheta * top.x + sintheta * top.y;
    tmp.y = -sintheta * top.x + costheta * top.y;
    top = tmp;
    tmp.x = costheta * bottom.x + sintheta * bottom.y;
    tmp.y = -sintheta * bottom.x + costheta * bottom.y;
    bottom = tmp;
    tmp.x = costheta * ul.x + sintheta * ul.y;
    tmp.y = -sintheta * ul.x + costheta * ul.y;
    ul = tmp;
    tmp.x = costheta * ur.x + sintheta * ur.y;
    tmp.y = -sintheta * ur.x + costheta * ur.y;
    ur = tmp;
    tmp.x = costheta * dl.x + sintheta * dl.y;
    tmp.y = -sintheta * dl.x + costheta * dl.y;
    dl = tmp;
    tmp.x = costheta * dr.x + sintheta * dr.y;
    tmp.y = -sintheta * dr.x + costheta * dr.y;
    dr = tmp;
    //scale
    double scale = 10.0 / fabs(l.x - r.x);
    l = scale * l;
    r = scale * r;
    top = scale * top;
    bottom = scale * bottom;
    ul = scale * ul;
    ur = scale * ur;
    dl = scale * dl;
    dr = scale * dr;
    normalized = true;
}

static double lbf::lookAtRot(double2 src, double2 tgt)
{
    const double pi = 3.1415926535898;
    const double minF = 0.0000000000001;
    double2 dir = tgt - src;
    if (fabs(dir.x) < minF)
        dir.x = 0;
    if (fabs(dir.y) < minF)
        dir.y = 0;
    double rot;
    if (dir.x == 0)
    {
        if (dir.y > 0)
            rot = pi / 2;
        else if (dir.y < 0)
            rot = pi * 3 / 2;
        else
            rot = 0;
    }
    else if (dir.x > 0)
    {
        rot = atan(dir.y / dir.x);
        if (dir.y > 0)
            rot = rot;
        else if (dir.y < 0)
            rot += 2 * pi;
        else
            rot = 0;
    }
    else
    {
        rot = atan(dir.y / dir.x);
        if (dir.y > 0)
            rot = rot + pi;
        else if (dir.y < 0)
            rot += pi;
        else
            rot = pi;
    }
    return rot;
}

void lbf::faceFilter(const cv::Mat& image, std::vector<cv::Rect>& faces, std::vector<int>& rejLvs, std::vector<double>& rejWs)
{
    std::vector<cv::Rect>::iterator faceIter = faces.begin();
    std::vector<int>::iterator lvIter = rejLvs.begin();
    std::vector<double>::iterator wIter = rejWs.begin();
    std::vector<cv::Rect> ffaces(1);
    std::vector<int> frejLvs(1);
    std::vector<double> frejWs(1);
    ffaces[0] = cv::Rect();
    frejLvs[0] = 0;
    frejWs[0] = 0;

    const double discardRatio = 0.8;
    while (faceIter != faces.end())
    {
        if ((*faceIter).width < image.rows / 2)
        {
            ++faceIter;
            ++lvIter;
            ++wIter;
            continue;
        }
        /* Higher level */
        if (*lvIter > frejLvs[0])
        {
            ffaces.clear();
            frejLvs.clear();
            frejWs.clear();
            ffaces.push_back(*faceIter);
            frejLvs.push_back(*lvIter);
            frejWs.push_back(*wIter);
        }
        /* Same level */
        else if (*lvIter == frejLvs[0])
        {
            /* Larger weight */
            if (*wIter > frejWs[0])
            {
                ffaces.clear();
                frejLvs.clear();
                frejWs.clear();
                ffaces.push_back(*faceIter);
                frejLvs.push_back(*lvIter);
                frejWs.push_back(*wIter);
            }
            else if (*wIter == frejWs[0])
            {
                ffaces.push_back(*faceIter);
                frejLvs.push_back(*lvIter);
                frejWs.push_back(*wIter);
            }
        }
        ++faceIter;
        ++lvIter;
        ++wIter;
    }
    /* The level is too low, discard */
    if (!ffaces.empty() && frejLvs[0] < discardRatio * _MAX_REJECT_LV)
    {
        ffaces.clear();
        frejLvs.clear();
        frejWs.clear();
    }
    faces = std::move(ffaces);
    rejLvs = std::move(frejLvs);
    rejWs = std::move(frejWs);
}

void lbf::faceDetect(const cv::Mat & image, const cv::Mat & image_flip, std::vector<cv::Rect>& faces)
{
    mytic();
    std::vector<int> rejectLv;
    std::vector<double> rejectW;
    _cc.detectMultiScale(image, faces, rejectLv, rejectW, 1.1, 3, 2, cv::Size(), cv::Size(), true);
    faceFilter(image, faces, rejectLv, rejectW);
    /* Flip */
    if (faces.empty())
    {
        _cc.detectMultiScale(image_flip, faces, rejectLv, rejectW, 1.1, 3, 2, cv::Size(), cv::Size(), true);
        faceFilter(image_flip, faces, rejectLv, rejectW);
        for (int i = 0; i < faces.size(); i++)
        {
            faces[i].x = image_flip.cols - faces[i].x - faces[i].width;
        }
    }
    mytoc("detection time");
}
