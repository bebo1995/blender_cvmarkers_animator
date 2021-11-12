#ifndef MARKER_H_
#define MARKER_H_

#include <iostream>
#include <eigen3/Eigen/Core>

namespace cvdetection
{
    enum boneMap
    {
        hips = 0,
        forearm_R = 1
    };

    class Marker
    {
    private:
        int id;
        std::string boneName;
        Eigen::Vector3d location;
        Eigen::Vector3d rotation;

    public:
        /**
         * @brief Marker instantiates a new empty object of the Marker class.
         * @return instance of Marker.
         */
        Marker();
        /**
         * @brief Marker instantiates a new object of the Marker class and sets its id, coordinates and rotation.
         * @param ID id of this marker.
         * @param locationVec 3D coordinates of the marker in the scene.
         * @param rotationVec 3D rotation vector (euler angles) of the marker in the scene.
         * @return instance of Marker.
         */
        Marker(const int &ID, const Eigen::Vector3d &locationVec, const Eigen::Vector3d &rotationVec);

    private:
        /**
         * @brief mapBone maps the Id of this marker to a Blender bone name.
         */
        void mapBone();

    public:
        /**
         * @brief setId sets the ID of this marker.
         * @param ID id of the marker.
         */
        void setId(const int &ID);
        /**
         * @brief setLocation sets the 3D coordinates of this marker.
         * @param locationVec coordinates of the marker.
         */
        void setLocation(const Eigen::Vector3d &locationVec);
        /**
         * @brief setrotation sets the 3D orientation (euler angles) of this marker.
         * @param rotationVec rotation vector of the marker.
         */
        void setRotation(const Eigen::Vector3d &rotationVec);
        /**
         * @brief getId returns the ID of this marker.
         * @return id of the marker.
         */
        int getId();
        /**
         * @brief getLocation returns the 3D coordinates of this marker.
         * @return coordinates of the marker.
         */
        Eigen::Vector3d getLocation();
        /**
         * @brief getRotation returns the 3D orientation (euler angles) of this marker.
         * @return rotation vector of the marker.
         */
        Eigen::Vector3d getRotation();
        /**
         * @brief getBoneName returns the name of the bone mapped to this marker.
         * @return name of the mapped bone.
         */
        std::string getBoneName();
    };
}

#endif