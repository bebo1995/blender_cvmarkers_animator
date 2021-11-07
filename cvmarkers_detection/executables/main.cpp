#include <opencv2/aruco/charuco.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <string>
#include <map>

#include <cvdetection/camera.hpp>

int main()
{
    cvdetection::Camera cam;
    //cam.calibrate("../../../cvmarkers_detection/calibration_input_settings.xml");
    cam.parseCalibrationParametersFromXml("../../../cvmarkers_detection/out_camera_data.xml");
    cv::VideoCapture video;
    video.open(0);
    video.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    video.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
    while (video.grab())
    {
        cv::Mat image;
        video.retrieve(image);
        std::map<int, std::map<std::string, cv::Vec3d>> markersPoses;
        cam.getArucoMarkersPoses(0.05, image, markersPoses);
        for (std::map<int, std::map<std::string, cv::Vec3d>>::iterator it = markersPoses.begin();
             it != markersPoses.end(); it++)
        {
            std::cout << it->first << " : " << std::endl;
            for (std::map<std::string, cv::Vec3d>::iterator it2 = markersPoses[it->first].begin();
                 it2 != markersPoses[it->first].end(); it2++)
            {
                std::cout << it2->first << " : " << it2->second << std::endl;
            }
        }
        cv::imshow("out", image);
        char key = (char)cv::waitKey(30);
        if (key == 27)
        { //if user press esc
            break;
        }
    }
}