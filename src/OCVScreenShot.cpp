#include "OCVScreenShot.hpp"

BITMAPINFOHEADER OCVScreenShot::createBitmapHeader(int width, int height)
{
    BITMAPINFOHEADER bi{};

    // create a bitmap
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = width;
    bi.biHeight = -height;  //this is the line that makes it draw upside down or not
    bi.biPlanes = 1;
    bi.biBitCount = 32;
    bi.biCompression = BI_RGB;
    bi.biSizeImage = 0;
    bi.biXPelsPerMeter = 0;
    bi.biYPelsPerMeter = 0;
    bi.biClrUsed = 0;
    bi.biClrImportant = 0;

    return bi;
}

// may make sense to have the class own the handles here so we can reuse the window handle during execution?
cv::Mat OCVScreenShot::captureScreenMat(HWND hwnd, MONITORINFO monInfo)
{
    cv::Mat src;

    // get handles to a device context (DC)
    HDC hwindowDC = GetDC(hwnd);
    // HDC hwindowDC = GetWindowDC(NULL);
    HDC hwindowCompatibleDC = CreateCompatibleDC(hwindowDC);
    SetStretchBltMode(hwindowCompatibleDC, COLORONCOLOR);

    // define scale, height and width
    // this captures the entire desktop area, we just want the primary as that's typically where folks will game
    /*int screenx = GetSystemMetrics(SM_XVIRTUALSCREEN);
    int screeny = GetSystemMetrics(SM_YVIRTUALSCREEN);
    int width = GetSystemMetrics(SM_CXVIRTUALSCREEN);
    int height = GetSystemMetrics(SM_CYVIRTUALSCREEN);*/

    // define scale, height and width
    int screenx = monInfo.rcMonitor.left;
    int screeny = monInfo.rcMonitor.top;
    int width = monInfo.rcMonitor.right;
    int height = monInfo.rcMonitor.bottom;

    // create mat object
    src.create(height, width, CV_8UC4);

    // create a bitmap
    HBITMAP hbwindow = CreateCompatibleBitmap(hwindowDC, width, height);
    BITMAPINFOHEADER bi = createBitmapHeader(width, height);

    // use the previously created device context with the bitmap
    SelectObject(hwindowCompatibleDC, hbwindow);

    // copy from the window device context to the bitmap device context
    StretchBlt(hwindowCompatibleDC, 0, 0, width, height, hwindowDC, screenx, screeny, width, height, SRCCOPY);  //change SRCCOPY to NOTSRCCOPY for wacky colors !
    GetDIBits(hwindowCompatibleDC, hbwindow, 0, height, src.data, (BITMAPINFO*)&bi, DIB_RGB_COLORS);            //copy from hwindowCompatibleDC to hbwindow

    // avoid memory leak
    DeleteObject(hbwindow);
    DeleteDC(hwindowCompatibleDC);
    ReleaseDC(hwnd, hwindowDC);

    return src;
}

void OCVScreenShot::screenShotToFile()
{
    // capture image
    auto hwnd = GetDesktopWindow();    
    auto monInfo = GetPrimaryMonitorInfo();
    cv::Mat src = captureScreenMat(hwnd, monInfo);

    fs::path ssPath = "C:\\touchstone-runner\\img\\screenshot.png";

    // save img
    cv::imwrite(ssPath.string(), src);
}

static HMONITOR GetPrimaryMonitorHandle()
{
    const POINT ptZero = { 0, 0 };
    return MonitorFromPoint(ptZero, MONITOR_DEFAULTTOPRIMARY);
}

MONITORINFO OCVScreenShot::GetPrimaryMonitorInfo()
{
    HMONITOR hmon = GetPrimaryMonitorHandle();
    
    MONITORINFO monInfo{};
    LPMONITORINFO pMonInfo = &monInfo;
    pMonInfo->cbSize = sizeof(MONITORINFO);
    auto res = GetMonitorInfoA(hmon, pMonInfo);
    if (!res) {
        std::cout << "failed to get monitor info\n";
    }
    return monInfo;
}
// https://devblogs.microsoft.com/oldnewthing/20070809-00/?p=25643