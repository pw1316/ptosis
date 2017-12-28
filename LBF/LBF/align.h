#pragma once
#pragma warning(disable: 4819)
#include <opencv2/opencv.hpp>

#include <string>

class Align
{
public:
    Align() {}
    Align(const std::string& modelName);
    ~Align();
    bool Load(const std::string& modelName);
    void Unload();
    bool IsLoaded() const;

    cv::Mat predict(const cv::Mat &im, const cv::Vec4d &bb);
private:
    bool _isLoaded = false;
    int _nStage = 0;
    int _nTree = 0;
    int _maxDepth = 0;
    cv::Mat _meanShape;
    double*** _regressor = nullptr;// [stage][landmarkcoord][landmark * tree * node]
    cv::Vec4d**** _forests = nullptr;// [stage][landmark][tree][node]
    int**** _threshold = nullptr;// [stage][landmark][tree][node]
};
