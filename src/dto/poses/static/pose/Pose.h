//
// Created by arseniy on 12.10.24.
//

#ifndef POSE_H
#define POSE_H
#include <array>

#include "eigen3/Eigen/Eigen"

class Pose
{
public:
    virtual ~Pose() = default;

    Pose() = default;
    Pose(const std::array<double, 3>& trans, const double rot[3][3]);

    Pose(const std::array<double, 3>& trans, std::array<std::array<double,3>,3> rot);

    Pose(const std::array<double, 3>& trans, Eigen::Quaterniond rot);

    Pose(const std::array<double, 3>& trans);

    virtual std::vector<double> flatten() const;

    virtual std::vector<double> flattenNoRot() const;

    virtual std::string toString() const;

    std::array<double, 3> translation;
    double rotation[3][3];
};




#endif
