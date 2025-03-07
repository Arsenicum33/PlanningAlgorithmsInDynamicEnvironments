//
// Created by arseniy on 2.1.25.
//

#ifndef KEYFRAME_H
#define KEYFRAME_H
#include "../static/Pose.h"


class Keyframe : public Pose
{
public:
    Keyframe(const std::array<double, 3>& trans, const double rot[3][3], double time)
        : Pose(trans, rot), time(time) {}

    Keyframe(const std::array<double, 3>& trans, std::array<std::array<double, 3>, 3> rot, double time)
        : Pose(trans, rot), time(time) {}

    Keyframe(const std::array<double, 3>& trans, Eigen::Quaterniond rot, double time)
        : Pose(trans, rot), time(time) {}

    Keyframe(const std::array<double, 3>& trans, double time)
        : Pose(trans), time(time) {}

    std::string toString() const override;

    double time;


};



#endif //KEYFRAME_H
