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
        /**
     * @brief Camera builds an empty instance of Camera. It has to be calibrated
     * with calibrate() (if the camera has never been calibrated) or 
     * parseCalibrationParametersFromXml() (if you have already saved 
     * camera calibration parameters).
     * @return instance of Camera.
     */
        Camera();

    public:
        /**
     * @brief calibrate calibrates the camera and saves parameters on a xml file. You
     * have to specify the xml path in the settings input xml file.
     * @param settingsPath path of the settings input xml file.
     * @param winSize is used to control the side length of the search window. Its default value is 11.
     * @param gridWidth is the measured distance between top-left (0, 0, 0) and 
     * top-right (s.squareSize*(s.boardSize.width-1), 0, 0) corners of the pattern grid points. If i's
     * different from -1, it will activate an alternative calibration method. This parameter is also set
     * in the input xml file. You have to change it in there if you don't want to change the calibration
     * method.
     * @return outcome of the calibration.
     */
        int calibrate(const std::string &settingsPath, const int &winSize = 11, const float &gridWith = -1);

    public:
        /**
     * @brief parseCalibrationParametersFromXml sets calibration parameters of
     * this instance of Camera by readung them from an xml file (built with calibration() method).
     * You should use this if you have already calibrated your camera with calibrate() method.
     * @return outcome of the method.
     */
        int parseCalibrationParametersFromXml(const std::string &parameters_xml_path);
        /**
     * @brief getCamMatrix returns a reference of the camera matrix obtained by calibration.
     * @param mat_ptr output reference of the camera matrix.
     */
        void getCamMatrix(cv::Mat *(&mat_ptr));
        /**
     * @brief getDistCoeffs returns a reference of the distance coefficents obtained by calibration.
     * @param mat_ptr output reference of the distance coefficents.
     */
        void getDistCoeffs(cv::Mat *(&mat_ptr));
    };
}

#endif