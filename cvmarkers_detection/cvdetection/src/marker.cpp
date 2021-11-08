#include <cvdetection/marker.hpp>

namespace cvdetection
{
    //---------- Marker class --------------------------------------------------------------->
    //---------- Constructors --------------------------------------------------------------->
    Marker::Marker() {}

    Marker::Marker(const int &ID, const Eigen::Vector3d &coordinatesVec, const Eigen::Vector3d &orientationVec)
    {
        this->id = ID;
        this->coordinates = coordinatesVec;
        this->orientation = orientationVec;
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

    void Marker::setOrientation(const Eigen::Vector3d &orientationVec)
    {
        this->orientation = orientationVec;
    }

    int Marker::getId()
    {
        return this->id;
    }

    void Marker::getCoordinates(Eigen::Vector3d &coordinatesVec)
    {
        coordinatesVec = this->coordinates;
    }

    void Marker::getOrientation(Eigen::Vector3d &orientationVec)
    {
        orientationVec = this->orientation;
    }
}