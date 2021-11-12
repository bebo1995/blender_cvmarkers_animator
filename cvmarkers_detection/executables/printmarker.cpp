#include <opencv2/highgui.hpp>
#include <opencv2/aruco/charuco.hpp>
#include <iostream>

#include <cvdetection/camera.hpp>

int main()
{
    cvdetection::Camera cam;
    cv::Mat markerImage;
    cam.getMarkersDictionary()->drawMarker(1, 500, markerImage);
    cv::imshow("out", markerImage);
    cv::waitKey(0);
}