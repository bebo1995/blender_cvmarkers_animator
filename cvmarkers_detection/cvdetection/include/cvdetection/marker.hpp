#ifndef MARKER_H_
#define MARKER_H_

#include <iostream>
#include <eigen3/Eigen/Core>

namespace cvdetection
{
    class Marker
    {
    private:
        int id;
        Eigen::Vector3d coordinates;
        Eigen::Vector3d orientation;

    public:
        /**
         * @brief Marker instantiates a new empty object of the Marker class.
         * @return instance of Marker.
         */
        Marker();
        /**
         * @brief Marker instantiates a new object of the Marker class and sets its id, coordinates and rotation.
         * @param ID id of this marker.
         * @param coordinatesVec 3D coordinates of the marker in the scene.
         * @param orientationVec 3D orientation of the marker in the scene.
         * @return instance of Marker.
         */
        Marker(const int &ID, const Eigen::Vector3d &coordinatesVec, const Eigen::Vector3d &orientationVec);

    public:
        /**
         * @brief setId sets the ID of this marker.
         * @param ID id of the marker.
         */
        void setId(const int &ID);
        /**
         * @brief setCoordinates sets the 3D coordinates of this marker.
         * @param coordinatesVec coordinates of the marker.
         */
        void setCoordinates(const Eigen::Vector3d &coordinatesVec);
        /**
         * @brief setOrientation sets the 3D orientation of this marker.
         * @param orientationVec orientation of the marker.
         */
        void setOrientation(const Eigen::Vector3d &orientationVec);
        /**
         * @brief getId returns the ID of this marker.
         * @return id of the marker.
         */
        int getId();
        /**
         * @brief getCoordinates returns the 3D coordinates of this marker.
         * @param coordinatesVec coordinates of the marker.
         */
        void getCoordinates(Eigen::Vector3d &coordinatesVec);
        /**
         * @brief getOrientation returns the 3D orientation of this marker.
         * @param orientationVec orientation of the marker.
         */
        void getOrientation(Eigen::Vector3d &orientationVec);
    };
}

#endif