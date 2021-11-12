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
    video.open(2);
    video.set(cv::CAP_PROP_FRAME_WIDTH, 1280); //640
    video.set(cv::CAP_PROP_FRAME_HEIGHT, 720); //480
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
        cam.getArucoMarkersPoses(0.1, image, markers, center, initialRotation);
        int count = 0;
        std::vector<cvdetection::Marker *> mappedMarkers;
        for (size_t i = 0; i < markers.size(); i++)
        {
            if (markers[i].getId() == 0 || markers[i].getId() == 1)
            {
                count++;
                mappedMarkers.push_back(&(markers[i]));
                if (!hipsMarkerfound && markers[i].getId() == 0)
                {
                    hipsMarkerfound = true;
                    center = markers[i].getLocation();
                    initialRotation = markers[i].getRotation();
                }
            }
        }
        if (count >= 1)
        {
            for (size_t i = 0; i < mappedMarkers.size(); i++)
            {
                cvdetection::Marker *mapMarker = mappedMarkers[i];
                std::string line;
                std::string boneName = mapMarker->getBoneName();
                Eigen::Vector3d loc = mapMarker->getLocation();
                Eigen::Vector3d rot = mapMarker->getRotation();
                line += boneName + ", " + std::to_string(loc[0]) + ", " + std::to_string(loc[1]) + ", " + std::to_string(loc[2]);
                line += ", " + std::to_string(rot[0]) + ", " + std::to_string(rot[1]) + ", " + std::to_string(rot[2]);
                output[std::to_string(mapMarker->getId())] = line;
            }
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