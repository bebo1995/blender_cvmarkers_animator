#include <eigen3/Eigen/Geometry>

#include <cvdetection/bone.hpp>

namespace cvdetection
{
    //---------- Bone class --------------------------------------------------------------->
    //---------- Constructor --------------------------------------------------------------->
    Bone::Bone(const std::string &boneName, const Marker &headJointMarker, const Marker &tailJointMarker)
    {
        this->name = boneName;
        this->headJoint = headJointMarker;
        this->tailJoint = tailJointMarker;
        //computing bone location
        Eigen::Vector3d headLocation;
        this->headJoint.getCoordinates(headLocation);
        this->location = headLocation;
        //computing bone euler angles
        Eigen::Matrix3d headRotation;
        Eigen::Matrix3d tailRotation;
        this->headJoint.getOrientation(headRotation);
        this->tailJoint.getOrientation(tailRotation);
        Eigen::Matrix3d head2TailRotation = headRotation.transpose() * tailRotation;
        this->rotation = head2TailRotation.eulerAngles(2, 1, 0);
    }

    //---------- Public methods --------------------------------------------------------------->

    void Bone::setName(const std::string &boneName)
    {
        this->name = boneName;
    }

    void Bone::getName(std::string &boneName)
    {
        boneName = this->name;
    }

    void Bone::getHeadJoint(Marker &headJointMarker)
    {
        headJointMarker = this->headJoint;
    }

    void Bone::getTailJoint(Marker &tailJointMarker)
    {
        tailJointMarker = this->tailJoint;
    }

    void Bone::getLocation(Eigen::Vector3d &boneLocation)
    {
        boneLocation = this->location;
    }

    void Bone::getRotation(Eigen::Vector3d &boneRotation)
    {
        boneRotation = this->rotation;
    }
}