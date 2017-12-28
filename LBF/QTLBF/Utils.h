#pragma once
#include <lbf.h>

#include <QtGui/QImage>

QImage cvMat2QImage(const cv::Mat& mat);
void debugLog(const char* format, ...);
