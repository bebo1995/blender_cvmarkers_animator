#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include <iostream>

namespace cvdetection
{
    class Camera
    {
    private:
        std::string calibrationParamsPath;

    public:
        Camera();

    public:
        int calibrate(const std::string &settingsPath, const int &winSize = 11, const float &gridWith = -1);

    public:
        void setCalibrationParamsPath(const std::string &path);
        std::string getCalibrationParamsPath();
    };
}

#endif