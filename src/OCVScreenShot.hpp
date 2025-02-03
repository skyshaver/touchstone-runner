#pragma once
#include <Windows.h>
#include <opencv2/opencv.hpp>
#include <filesystem>

namespace fs = std::filesystem;

class OCVScreenShot
{

private:
    BITMAPINFOHEADER createBitmapHeader(int width, int height);

public:
    cv::Mat captureScreenMat(HWND hwnd);
    void screenShotToFile();
};



