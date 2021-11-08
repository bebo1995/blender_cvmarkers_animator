#ifndef BONE_H_
#define BONE_H_

#include <iostream>
#include <eigen3/Eigen/Core>

#include <cvdetection/marker.hpp>

namespace cvdetection
{
    class Bone
    {
    private:
        std::string name;
        Marker headJoint;
        Marker tailJoint;
        Eigen::Vector3d location;
        Eigen::Vector3d rotation;

    public:
        /**
         * @brief Bone instantiates an object of Bone, sets the headJointMarker as its parent joint
         * and the tailJointMarker as its child joint; then computes location and euler rotation XYZ vectors
         * of this bone. A Bone object represents a rigging armature bone of a 3D model.
         * @param boneName bone name.
         * @param headJointMarker marker to be set as parent joint of the bone.
         * @param tailJointMarker marker to be set as child joint of the bone.
         * @return instance of Bone.
         */
        Bone(const std::string &boneName, const Marker &headJointMarker, const Marker &tailJointMarker);

    public:
        /**
         * @brief setName sets bone name.
         * @param boneName bone name.
         */
        void setName(const std::string &boneName);
        /**
         * @brief getName returns bone name.
         * @param boneName bone name.
         */
        void getName(std::string &boneName);
        /**
         * @brief getHeadJoint returns head joint marker.
         * @param headJointMarker marker of the parent joint.
         */
        void getHeadJoint(Marker &headJointMarker);
        /**
         * @brief getHeadJoint returns tail joint marker.
         * @param headJointMarker marker of the child joint.
         */
        void getTailJoint(Marker &tailJointMarker);
        /**
         * @brief getLocation returns bone location vector.
         * @param boneLocation bone location 3D vector.
         */
        void getLocation(Eigen::Vector3d &boneLocation);
        /**
         * @brief getRotation returns bone euler rotation vector.
         * @param boneRotation bone euler rotation 3D vector.
         */
        void getRotation(Eigen::Vector3d &boneRotation);
    };
}

#endif