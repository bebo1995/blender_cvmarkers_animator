#include <cvdetection/marker.hpp>

namespace cvdetection
{
    //---------- Marker class --------------------------------------------------------------->
    //---------- Constructors --------------------------------------------------------------->
    Marker::Marker() {}

    Marker::Marker(const int &ID, const Eigen::Vector3d &coordinatesVec, const Eigen::Vector3d &orientationMat)
    {
        this->id = ID;
        this->location = coordinatesVec;
        this->rotation = orientationMat;
        this->mapBone();
    }

    //---------- Private methods --------------------------------------------------------------->
    void Marker::mapBone()
    {
        switch (this->id)
        {
        case boneMap::hips:
            this->boneName = "hips";
            break;
        case boneMap::forearm_R:
            this->boneName = "forearm.R";
            break;
        default:
            this->boneName = "";
            break;
        }
    }

    //---------- Public methods --------------------------------------------------------------->
    void Marker::setId(const int &ID)
    {
        this->id = ID;
        this->mapBone();
    }

    void Marker::setLocation(const Eigen::Vector3d &locationVec)
    {
        this->location = locationVec;
    }

    void Marker::setRotation(const Eigen::Vector3d &rotationVec)
    {
        this->rotation = rotationVec;
    }

    int Marker::getId()
    {
        return this->id;
    }

    Eigen::Vector3d Marker::getLocation()
    {
        return this->location;
    }

    Eigen::Vector3d Marker::getRotation()
    {
        return this->rotation;
    }

    std::string Marker::getBoneName()
    {
        return this->boneName;
    }
}