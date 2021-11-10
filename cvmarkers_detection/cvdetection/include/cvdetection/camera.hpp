#ifndef CAMERA_H_
#define CAMERA_H_

#include <iostream>
#include <map>

#include <cvdetection/marker.hpp>

namespace cvdetection
{
    class Camera
    {
    private:
        cv::Mat camMatrix;
        cv::Mat distCoeffs;
        cv::Ptr<cv::aruco::Dictionary> markersDictionary;

    public:
        /**
         * @brief Camera builds an empty instance of Camera. It has to be calibrated
         * with calibrate() (if the camera has never been calibrated) or 
         * parseCalibrationParametersFromXml() (if you have already saved 
         * camera calibration parameters). It sets a predefined aruco markers dictionary that 
         * camera can detect.
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
         * different from -1, it will activate an alternative calibration method. This parameter is also 
         * set by using Square_Size field in the input xml file. You have to change it in there if you 
         * don't want to change the calibration method.
         * @return outcome of the calibration.
         */
        int calibrate(const std::string &settingsPath, const int &winSize = 11, const float &gridWith = -1);
        /**
         * @brief parseCalibrationParametersFromXml sets calibration parameters of
         * this instance of Camera by readung them from an xml file (built with calibration() method).
         * You should use this if you have already calibrated your camera with calibrate() method.
         * @return outcome of the method.
         */
        int parseCalibrationParametersFromXml(const std::string &parameters_xml_path);
        /**
         * @brief getArucoMarkersPoses estimates the aruco markers' poses from the passed image.
         * @param markerSide side of the markers in the scene in meters.
         * @param image to be analyzed.
         * @param detectedMarkers vector containing all Aruco markers detected in the image.
         * @param center 3D coordinates of the center of the scene (default = 0,0,0).
         */
        void getArucoMarkersPoses(const float &markerSide, cv::InputOutputArray &image,
                                  std::vector<Marker> &detectedMarkers, const Eigen::Vector3d &center = Eigen::Vector3d(0, 0, 0));

    public:
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
        /**
         * @brief setMarkersDictionary sets the markers' dictionary this instance of Camera can detect to.
         * @param dictionary dictionary to detect.
         */
        void setMarkersDictionary(const cv::Ptr<cv::aruco::Dictionary> &dictionary);
        /**
         * @brief getMarkersDictionary returns tge dictionary this instance of Camera is detecting to.
         * @return detected dictionary.
         */
        cv::Ptr<cv::aruco::Dictionary> getMarkersDictionary();
    };
}

#endif