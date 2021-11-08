#include <cvdetection/marker.hpp>

namespace cvdetection
{
    //---------- Marker class --------------------------------------------------------------->
    //---------- Constructors --------------------------------------------------------------->
    Marker::Marker() {}

    Marker::Marker(const int &ID, const Eigen::Vector3d &coordinatesVec, const Eigen::Matrix3d &orientationMat)
    {
        this->id = ID;
        this->coordinates = coordinatesVec;
        this->orientation = orientationMat;
    }

    //---------- Public methods --------------------------------------------------------------->
    void Marker::setId(const int &ID)
    {
        this->id = ID;
    }

    void Marker::setCoordinates(const Eigen::Vector3d &coordinatesVec)
    {
        this->coordinates = coordinatesVec;
    }

    void Marker::setOrientation(const Eigen::Matrix3d &orientationMat)
    {
        this->orientation = orientationMat;
    }

    int Marker::getId()
    {
        return this->id;
    }

    void Marker::getCoordinates(Eigen::Vector3d &coordinatesVec)
    {
        coordinatesVec = this->coordinates;
    }

    void Marker::getOrientation(Eigen::Matrix3d &orientationMat)
    {
        orientationMat = this->orientation;
    }
}