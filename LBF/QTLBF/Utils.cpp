#include "Utils.h"

#include <stdarg.h>

QImage cvMat2QImage(const cv::Mat & mat)
{
    QImage img;
    if (mat.type() == CV_8UC1)
    {
        img = QImage(mat.data, mat.cols, mat.rows, (int)mat.step, QImage::Format_Indexed8);
        return img;
    }
    else if (mat.type() == CV_8UC3)
    {
        img = QImage(mat.data, mat.cols, mat.rows, (int)mat.step, QImage::Format_RGB888);
        return img.rgbSwapped();
    }
    else
    {
        return img;
    }
}

void debugLog(const char * format, ...)
{
    static long long counter = 0;
    va_list args;
    va_start(args, format);
    char buf[256];
    sprintf(buf, "log\\%020lld", counter);
    vsprintf(buf + strlen(buf), format, args);
    sprintf(buf + strlen(buf), ".png");
    cv::imwrite(buf, cv::Mat());
    va_end(args);
    ++counter;
}
