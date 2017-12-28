#ifndef __LBF_H__
#define __LBF_H__
/* The file contains a character that cannot be represented in the current code page (number).Save the file in Unicode format to prevent data loss. */
#pragma warning(disable: 4819)

#ifdef _WIN32
#ifdef LBF_DLL
#ifdef LBF_BUILD_LIB
#define LBF_API __declspec(dllexport)
#else
#define LBF_API __declspec(dllimport)
#endif
#else
#define LBF_API extern
#endif
#else
#define LBF_API extern
#endif

#include "struct.hpp"
#include <opencv2/opencv.hpp>

#include <string>

//#define DUMP_FRAME
//#define DUMP_SHAPE

//#define ENABLE_TIC
#ifdef ENABLE_TIC
#define mytic() tic()
#define mytoc(expr) toc((expr))
#else
#define mytic() ((void)0)
#define mytoc(expr) ((void)0)
#endif

//#define ENABLE_LOG
#ifdef ENABLE_LOG
#define lbf_log printf
#else
#define lbf_log
#endif

#define ENABLE_ASSERT

namespace lbf {
    using LBF_ERR_CODE = enum
    {
        LBF_ERR_SUCC = 0,
        LBF_ERR_NO_HAAR = 1,
        LBF_ERR_NO_ALIGN = 2,
        LBF_ERR_IO_FAIL = 3
    };

    LBF_API bool loadHaarCascade();
    LBF_API bool loadHaarCascade(const std::string& cascadeName);
    LBF_API void unloadHaarCascade();
    LBF_API bool isHaarLoaded();

    LBF_API bool loadAlignCascade();
    LBF_API bool loadAlignCascade(const std::string& cascadeName);
    LBF_API void unloadAlignCascade();
    LBF_API bool isAlignLoaded();

    /* Align by file name, If no faces, vector is empty */
    LBF_API int alignImage(const std::string imgPath, cv::Mat& outImg, std::vector<double2>& outShape);
    /* Align by cv::Mat, If no faces, vector is empty */
    LBF_API int alignImage(const cv::Mat& img, std::vector<double2>& outShape);

    /* Align by video name */
    LBF_API int alignVideo(const std::string videoPath, CvCapture*& outFrames, std::vector<std::vector<double2>>& outShapes);
    /* Align by CvCapture */
    LBF_API int alignVideo(CvCapture* const& frames, std::vector<std::vector<double2>>& outShapes);

    LBF_API void getEyeDataFromShapes(const std::vector<std::vector<double2>>& shapes, std::vector<double>& outLEye, std::vector<double>& outREye);
    LBF_API void getEyeDataFromFile(const std::string& shapesPath, std::vector<double>& outLEye, std::vector<double>& outREye);
    LBF_API void getTickFromData(const std::vector<double>& eyeData, int& outCnt);
}

#endif