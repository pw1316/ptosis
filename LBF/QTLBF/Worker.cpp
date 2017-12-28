#include "Worker.h"

#include <lbf.h>

#include <fstream>

#include "Log.h"

void LoadAlignWorker::Run()
{
    bool isdone = false;
    if (filename.isEmpty())
        isdone = lbf::loadAlignCascade();
    else
        isdone = lbf::loadAlignCascade(filename.toStdString());
    emit Done(isdone);
}

AlignWorker::AlignWorker(CvCapture* _capture, std::vector<std::vector<double2>>* _pshapes, double* _pscale)
{
    capture = _capture;
    pshapes = _pshapes;
    pscale = _pscale;
}

void AlignWorker::Run()
{
    progressValue = 0;
    int curFrame = 0;
    int totFrames = cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_COUNT);
    cvSetCaptureProperty(capture, CV_CAP_PROP_POS_FRAMES, 0);
    int ret = 0;
    pshapes->clear();
    while (true)
    {
        IplImage* iplImg = cvQueryFrame(capture);
        cv::Mat image = cv::cvarrToMat(iplImg);
        if (image.empty())
        {
            break;
        }
        if (iplImg->origin != IPL_ORIGIN_TL)
            flip(image, image, 0);
        if (*pscale < 1) {
            cv::resize(image, image, cv::Size(), *pscale, *pscale, CV_INTER_AREA);
        }
        else {
            cv::resize(image, image, cv::Size(), *pscale, *pscale, CV_INTER_LINEAR);
        }
        pshapes->push_back(std::vector<double2>());
        int tmpret = lbf::alignImage(image, (*pshapes)[curFrame++]);
        pwinfo("processing frame %04d: size %d", curFrame - 1, (*pshapes)[curFrame - 1].size());
        ret |= tmpret;

        int curProgress = curFrame * 100 / totFrames;
        if (curProgress > progressValue)
        {
            progressValue = curProgress;
            emit UpdateProgress(progressValue);
        }
    }
    emit UpdateProgress(100);

    /* Dump */
    //std::ofstream oFile("Shape.csv");
    //for (int i = 0; i < pshapes->size(); i++)
    //{
    //    oFile << "F" << std::endl;
    //    for (int j = 0; j < (*pshapes)[i].size(); j++)
    //    {
    //        oFile << (*pshapes)[i][j].x << ", " << (*pshapes)[i][j].y << std::endl;
    //    }
    //}
    //oFile.close();

    emit Done((ret == 0) ? true : false);
}
