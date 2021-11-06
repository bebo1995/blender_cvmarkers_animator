#include <opencv2/aruco/charuco.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <string>

#include <cvdetection/camera.hpp>

void detectCharucoBoardWithCalibrationPose(const cv::Mat &cameraMatrix, const cv::Mat &distCoeffs)
{
    cv::VideoCapture inputVideo;
    inputVideo.open(0);
    cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);
    cv::Ptr<cv::aruco::CharucoBoard> board = cv::aruco::CharucoBoard::create(5, 7, 0.04f, 0.02f, dictionary);
    cv::Ptr<cv::aruco::DetectorParameters> params = cv::aruco::DetectorParameters::create();
    while (inputVideo.grab())
    {
        cv::Mat image;
        cv::Mat imageCopy;
        inputVideo.retrieve(image);
        image.copyTo(imageCopy);
        std::vector<int> markerIds;
        std::vector<std::vector<cv::Point2f>> markerCorners;
        cv::aruco::detectMarkers(image, board->dictionary, markerCorners, markerIds, params);
        // if at least one marker detected
        if (markerIds.size() > 0)
        {
            cv::aruco::drawDetectedMarkers(imageCopy, markerCorners, markerIds);
            std::vector<cv::Point2f> charucoCorners;
            std::vector<int> charucoIds;
            cv::aruco::interpolateCornersCharuco(markerCorners, markerIds, image, board, charucoCorners, charucoIds, cameraMatrix, distCoeffs);
            // if at least one charuco corner detected
            if (charucoIds.size() > 0)
            {
                cv::Scalar color = cv::Scalar(255, 0, 0);
                cv::aruco::drawDetectedCornersCharuco(imageCopy, charucoCorners, charucoIds, color);
                cv::Vec3d rvec, tvec;
                // cv::aruco::estimatePoseCharucoBoard(charucoCorners, charucoIds, board, cameraMatrix, distCoeffs, rvec, tvec);
                bool valid = cv::aruco::estimatePoseCharucoBoard(charucoCorners, charucoIds, board, cameraMatrix, distCoeffs, rvec, tvec);
                // if charuco pose is valid
                if (valid)
                    cv::aruco::drawAxis(imageCopy, cameraMatrix, distCoeffs, rvec, tvec, 0.1f);
            }
        }
        cv::imshow("out", imageCopy);
        char key = (char)cv::waitKey(30);
        if (key == 27)
            break;
    }
}

int main()
{
    cvdetection::Camera cam;
    //cam.calibrate("../../../cvmarkers_detection/calibration_input_settings.xml");
    cam.parseCalibrationParametersFromXml("../../../cvmarkers_detection/out_camera_data.xml");
    cv::Mat *camMat;
    cam.getCamMatrix(camMat);
    cv::Mat *dCoeffs;
    cam.getDistCoeffs(dCoeffs);
    std::cout << camMat->rowRange(0, 3) << std::endl;
    std::cout << dCoeffs->rowRange(0, 5) << std::endl;
    detectCharucoBoardWithCalibrationPose(*camMat, *dCoeffs);
}