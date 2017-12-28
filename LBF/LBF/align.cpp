#include "align.h"

#include <fstream>

#define LANDMARK_NUM 75

Align::Align(const std::string& modelName)
{
    Load(modelName);
}

Align::~Align()
{
    Unload();
}

bool Align::Load(const std::string & modelName)
{
    Unload();/* Remove previous model */
    std::ifstream inputFile;
    inputFile.open(modelName, std::ios::binary);
    if (!inputFile.is_open())
    {
        _isLoaded = false;
        return false;
    }
    inputFile.read(reinterpret_cast<char*>(&_nStage), sizeof(int));
    inputFile.read(reinterpret_cast<char*>(&_nTree), sizeof(int));
    inputFile.read(reinterpret_cast<char*>(&_maxDepth), sizeof(int));
    inputFile.seekg(sizeof(int), std::ios::cur);

    /* Allocate Memory */
    _meanShape.create(LANDMARK_NUM, 2, CV_64FC1);
    _forests = new cv::Vec4d***[_nStage];
    _threshold = new int***[_nStage];
    _regressor = new double**[_nStage];
    for (int stageId = 0; stageId < _nStage; stageId++) {
        _forests[stageId] = new cv::Vec4d**[LANDMARK_NUM];
        _threshold[stageId] = new int**[LANDMARK_NUM];
        _regressor[stageId] = new double*[2 * LANDMARK_NUM];
        for (int landmarkId = 0; landmarkId < LANDMARK_NUM; landmarkId++) {
            _forests[stageId][landmarkId] = new cv::Vec4d*[_nTree];
            _threshold[stageId][landmarkId] = new int*[_nTree];
            for (int treeId = 0; treeId < _nTree; treeId++) {
                _forests[stageId][landmarkId][treeId] = new cv::Vec4d[1i64 << (_maxDepth - 1)];
                _threshold[stageId][landmarkId][treeId] = new int[1i64 << (_maxDepth - 1)];
            }
        }
        for (int coordId = 0; coordId < 2 * LANDMARK_NUM; coordId++)
            _regressor[stageId][coordId] = new double[LANDMARK_NUM * _nTree * (1 << (_maxDepth - 1))];
    }
    /* Allocate Memory */

    for (int landmarkId = 0; landmarkId < LANDMARK_NUM; landmarkId++)
        inputFile.read(_meanShape.ptr<char>(landmarkId), sizeof(double) * _meanShape.cols);
    for (int stageId = 0; stageId < _nStage; stageId++) {
        for (int landmarkId = 0; landmarkId < LANDMARK_NUM; landmarkId++) {
            for (int treeId = 0; treeId < _nTree; treeId++) {
                inputFile.read(reinterpret_cast<char*>(&_forests[stageId][landmarkId][treeId][1]), sizeof(cv::Vec4d) * ((1 << (_maxDepth - 1)) - 1));
                inputFile.read(reinterpret_cast<char*>(&_threshold[stageId][landmarkId][treeId][1]), sizeof(int) * ((1 << (_maxDepth - 1)) - 1));
            }
        }
        for (int coordId = 0; coordId < 2 * LANDMARK_NUM; coordId++)
            inputFile.read(reinterpret_cast<char*>(&_regressor[stageId][coordId][0]), sizeof(double) * (LANDMARK_NUM * _nTree * (1 << (_maxDepth - 1))));
    }
    inputFile.close();
    _isLoaded = true;
    return true;
}

void Align::Unload()
{
    if (!_isLoaded)
    {
        return;
    }
    for (int stageId = 0; stageId < _nStage; stageId++) {
        for (int landmarkId = 0; landmarkId < LANDMARK_NUM; landmarkId++) {
            for (int treeId = 0; treeId < _nTree; treeId++) {
                delete[] _forests[stageId][landmarkId][treeId];
                delete[] _threshold[stageId][landmarkId][treeId];
            }
            delete[] _forests[stageId][landmarkId];
            delete[] _threshold[stageId][landmarkId];
        }
        for (int coordId = 0; coordId < 2 * LANDMARK_NUM; coordId++)
            delete[] _regressor[stageId][coordId];
        delete[] _forests[stageId];
        delete[] _threshold[stageId];
        delete[] _regressor[stageId];
    }
    delete[] _forests;
    delete[] _threshold;
    delete[] _regressor;
    _isLoaded = false;
}

bool Align::IsLoaded() const
{
    return _isLoaded;
}

static cv::Mat_<double> projectShape(const cv::Mat_<double>& shape, const cv::Vec4d& boundBox)
{
    cv::Mat_<double> ret = shape.clone();
    for (int landmarkId = 0; landmarkId < LANDMARK_NUM; landmarkId++) {
        ret(landmarkId, 0) = (ret(landmarkId, 0) - boundBox[0]) / boundBox[2];
        ret(landmarkId, 1) = (ret(landmarkId, 1) - boundBox[1]) / boundBox[3];
    }
    return ret;
}

static cv::Mat_<double> reprojectShape(const cv::Mat_<double>& shape, const cv::Vec4d& boundBox)
{
    cv::Mat_<double> ret = shape.clone();
    for (int landmarkId = 0; landmarkId < LANDMARK_NUM; landmarkId++) {
        ret(landmarkId, 0) = ret(landmarkId, 0) * boundBox[2] + boundBox[0];
        ret(landmarkId, 1) = ret(landmarkId, 1) * boundBox[3] + boundBox[1];
    }
    return ret;
}

/* shape is projected shape */
static void similarityTransform(const cv::Mat_<double>& shape1, const cv::Mat_<double>& shape2, cv::Matx22d& rotation, double& scale)
{
    cv::Mat_<double> ts1(75, 2);
    cv::Mat_<double> ts2(75, 2);
    ts1.col(0) = shape1.col(0) - mean(shape1.col(0))[0];
    ts1.col(1) = shape1.col(1) - mean(shape1.col(1))[0];
    ts2.col(0) = shape2.col(0) - mean(shape2.col(0))[0];
    ts2.col(1) = shape2.col(1) - mean(shape2.col(1))[0];
    cv::Mat c1, c2, m1, m2;
    calcCovarMatrix(ts1, c1, m1, CV_COVAR_COLS);
    calcCovarMatrix(ts2, c2, m2, CV_COVAR_COLS);
    double num = ts1.col(1).dot(ts2.col(0)) - ts1.col(0).dot(ts2.col(1));
    double den = ts1.col(0).dot(ts2.col(0)) + ts1.col(1).dot(ts2.col(1));
    scale = sqrt(norm(c1) / norm(c2));
    rotation(0, 0) = den; rotation(0, 1) = -num;
    rotation(1, 0) = num; rotation(1, 1) = den;
    rotation = rotation * (1.0 / sqrt(num * num + den * den));
}

template<typename T>
static inline T clamp(T tgt, T low, T high)
{
    return cv::max(cv::min(tgt, high), low);
}

cv::Mat Align::predict(const cv::Mat &image, const cv::Vec4d &boundBox)
{
    cv::Mat_<double> currentShape = _meanShape.clone();
    /* To Absolute Position */
    currentShape = reprojectShape(currentShape, boundBox);
    for (int stageId = 0; stageId < _nStage; stageId++) {
        /* Rotation Matrix */
        cv::Matx22d r;
        double s;
        similarityTransform(projectShape(currentShape, boundBox), _meanShape, r, s);
        /* Rotation Matrix */

        int b = 1 << (_maxDepth - 1);
        cv::Mat_<double> deltaShape = cv::Mat::zeros(75, 2, CV_64FC1);
        for (int landmarkId = 0; landmarkId < 75; landmarkId++) {
            for (int treeId = 0; treeId < _nTree; treeId++) {
                int nodeId = 1;
                for (int t = 1; t < _maxDepth; t++) {
                    const cv::Vec4d f = _forests[stageId][landmarkId][treeId][nodeId];
                    int fea1 = (int)image.at<uchar>(
                        clamp(int(s * (r(1, 0) * f[0] + r(1, 1) * f[1]) * boundBox[3] + currentShape(landmarkId, 1) + 0.5), 0, image.rows - 1),
                        clamp(int(s * (r(0, 0) * f[0] + r(0, 1) * f[1]) * boundBox[2] + currentShape(landmarkId, 0) + 0.5), 0, image.cols - 1)
                        );
                    int fea2 = (int)image.at<uchar>(
                        clamp(int(s * (r(1, 0) * f[2] + r(1, 1) * f[3]) * boundBox[3] + currentShape(landmarkId, 1) + 0.5), 0, image.rows - 1),
                        clamp(int(s * (r(0, 0) * f[2] + r(0, 1) * f[3]) * boundBox[2] + currentShape(landmarkId, 0) + 0.5), 0, image.cols - 1)
                        );
                    int threshold = _threshold[stageId][landmarkId][treeId][nodeId];
                    nodeId = 2 * nodeId + (fea1 - fea2 < threshold ? 0 : 1);
                }
                const int leafId = (landmarkId * _nTree + treeId - 1) * b + nodeId;
                for (int landmarkId = 0; landmarkId < LANDMARK_NUM; landmarkId++) {
                    deltaShape(landmarkId, 0) += _regressor[stageId][2 * landmarkId + 0][leafId];
                    deltaShape(landmarkId, 1) += _regressor[stageId][2 * landmarkId + 1][leafId];
                }
            }
        }
        for (int landmarkId = 0; landmarkId < LANDMARK_NUM; landmarkId++) {
            deltaShape(landmarkId, 0) *= boundBox[2];
            deltaShape(landmarkId, 1) *= boundBox[3];
        }
        currentShape += s * deltaShape * cv::Mat(r.t());
    }
    return currentShape;
}
