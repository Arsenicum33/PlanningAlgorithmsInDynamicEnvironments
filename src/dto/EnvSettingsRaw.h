//
// Created by arseniy on 7.3.25.
//

#ifndef ENVSETTINGSRAW_H
#define ENVSETTINGSRAW_H
#include <string>
#include <variant>
#include <poses/static/Pose.h>

#include "ConfigurationSpaceBoundaries.h"

class EnvSettingsRaw
{
public:
    EnvSettingsRaw(const Pose& startPose, const std::variant<Pose, std::string>& target, const ConfigurationSpaceBoundaries& boundaries, const std::string& agentFilepath, const std::string& obstaclesFilepath,
                const std::vector<std::string> &dynamicObjectsFilepaths = std::vector<std::string>()) :
        startPose(startPose), target(target), boundaries(boundaries), agentFilepath(agentFilepath), obstaclesFilepath(obstaclesFilepath),
        dynamicObjectsFilepaths(dynamicObjectsFilepaths){}
    Pose startPose;
    std::variant<Pose, std::string> target;
    ConfigurationSpaceBoundaries boundaries;
    std::string agentFilepath;
    std::string obstaclesFilepath;
    std::vector<std::string> dynamicObjectsFilepaths;
};
#endif //ENVSETTINGSRAW_H
