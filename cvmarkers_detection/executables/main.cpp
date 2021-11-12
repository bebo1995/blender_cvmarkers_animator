#include <opencv2/aruco/charuco.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <eigen3/Eigen/Core>

#include <cvdetection/camera.hpp>
#include <cvdetection/marker.hpp>

int main()
{
    cvdetection::Camera cam;
    //cam.calibrate("../../../cvmarkers_detection/calibration_input_settings.xml");
    cam.parseCalibrationParametersFromXml("../../../cvmarkers_detection/out_camera_data.xml");
    cv::VideoCapture video;
    video.open(0);
    video.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    video.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
    std::map<std::string, std::string> output;
    std::string firstLineOutput = "boneName, locationX, locationY, locationZ, rotationX, rotationY, rotationZ";
    output["-1"] = firstLineOutput;
    bool hipsMarkerfound = false;
    Eigen::Vector3d center(0, 0, 0);
    Eigen::Vector3d initialRotation(0, 0, 0);
    while (video.grab())
    {
        cv::Mat image;
        video.retrieve(image);
        std::vector<cvdetection::Marker> markers;
        cam.getArucoMarkersPoses(0.05, image, markers, center, initialRotation);
        int count = 0;
        cvdetection::Marker *hipsMarker;
        for (size_t i = 0; i < markers.size(); i++)
        {
            if (markers[i].getId() == 0)
            {
                count++;
                hipsMarker = &(markers[i]);
                if (!hipsMarkerfound)
                {
                    hipsMarkerfound = true;
                    center = markers[i].getLocation();
                    //initialRotation = markers[i].getRotation();
                    initialRotation = Eigen::Vector3d(0, M_PI, 0);
                }
            }
        }
        if (count >= 1)
        {
            std::string line;
            std::string boneName = hipsMarker->getBoneName();
            Eigen::Vector3d loc = hipsMarker->getLocation();
            Eigen::Vector3d rot = hipsMarker->getRotation();
            line += boneName + ", " + std::to_string(loc[0]) + ", " + std::to_string(loc[1]) + ", " + std::to_string(loc[2]);
            line += ", " + std::to_string(rot[0]) + ", " + std::to_string(rot[1]) + ", " + std::to_string(rot[2]);
            output["0"] = line;
            std::ofstream myfile("../../../detectedBones.csv");
            for (std::map<std::string, std::string>::iterator it = output.begin(); it != output.end(); ++it)
            {
                myfile << it->second << std::endl;
            }
            myfile.close();
        }
        cv::imshow("out", image);
        char key = (char)cv::waitKey(30);
        if (key == 27)
        { //if user press esc
            break;
        }
    }
}