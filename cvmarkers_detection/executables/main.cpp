#include <opencv2/aruco/charuco.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <eigen3/Eigen/Core>

#include <cvdetection/camera.hpp>
#include <cvdetection/marker.hpp>
#include <cvdetection/bone.hpp>

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
    bool rootBoneFound = false;
    Eigen::Vector3d center(0, 0, 0);
    while (video.grab())
    {
        cv::Mat image;
        video.retrieve(image);
        std::vector<cvdetection::Marker> markers;
        cam.getArucoMarkersPoses(0.05, image, markers, center);
        std::array<cvdetection::Marker, 2> hipsJoints;
        cvdetection::Bone *hips;
        int count = 0;
        for (cvdetection::Marker marker : markers)
        {
            if (marker.getId() == 0)
            {
                hipsJoints[0] = marker;
                count++;
                if (!rootBoneFound)
                {
                    marker.getCoordinates(center);
                    rootBoneFound = true;
                }
            }
            if (marker.getId() == 1)
            {
                hipsJoints[1] = marker;
                count++;
            }
        }
        if (count >= 2)
        {
            hips = new cvdetection::Bone("hips", hipsJoints[0], hipsJoints[1]);
            std::string line;
            Eigen::Vector3d loc;
            Eigen::Vector3d rot;
            hips->getName(line);
            hips->getLocation(loc);
            hips->getRotation(rot);
            line += ", " + std::to_string(loc[0]) + ", " + std::to_string(loc[1]) + ", " + std::to_string(loc[2]);
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