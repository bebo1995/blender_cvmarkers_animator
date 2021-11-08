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
    std::string firstLineOutput = "markerID, coordinateX, coordinateY, coordinateZ, orientationX, orientationY, orientationZ";
    output["-1"] = firstLineOutput;
    while (video.grab())
    {
        cv::Mat image;
        video.retrieve(image);
        std::vector<cvdetection::Marker> markers;
        cam.getArucoMarkersPoses(0.05, image, markers);
        for (cvdetection::Marker marker : markers)
        {
            Eigen::Vector3d coordinates;
            Eigen::Vector3d orientation;
            marker.getCoordinates(coordinates);
            marker.getOrientation(orientation);
            std::string line = std::to_string(marker.getId()) + ", " +
                               std::to_string(coordinates[0]) + ", " +
                               std::to_string(coordinates[1]) + ", " +
                               std::to_string(coordinates[2]) + ", " +
                               std::to_string(orientation[0]) + ", " +
                               std::to_string(orientation[1]) + ", " +
                               std::to_string(orientation[2]);
            output[std::to_string(marker.getId())] = line;
        }
        std::ofstream myfile("../../../markersDetection.csv");
        for (std::map<std::string, std::string>::iterator it = output.begin(); it != output.end(); ++it)
        {
            myfile << it->second << std::endl;
        }
        myfile.close();
        cv::imshow("out", image);
        char key = (char)cv::waitKey(30);
        if (key == 27)
        { //if user press esc
            break;
        }
    }
}