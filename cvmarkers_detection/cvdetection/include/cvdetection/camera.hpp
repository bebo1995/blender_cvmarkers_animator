#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include <iostream>
#include <memory>

namespace cvdetection
{
    class Camera
    {
    private:
        cv::Mat camMatrix;
        cv::Mat distCoeffs;

    public:
        Camera();

    public:
        int calibrate(const std::string &settingsPath, const int &winSize = 11, const float &gridWith = -1);

    public:
        int parseCalibrationParametersFromXml(const std::string &parameters_xml_path);
        void getCamMatrix(cv::Mat *(&mat_ptr));
        void getDistCoeffs(cv::Mat *(&mat_ptr));
    };
}

#endif