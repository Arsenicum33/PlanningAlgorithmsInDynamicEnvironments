//
// Created by arseniy on 25.10.24.
//

#ifndef ENVSETTINGS_H
#define ENVSETTINGS_H
#include <RAPID.H>
#include <variant>
#include <dto/configurationSpaceBoundaries/ConfigurationSpaceBoundaries.h>
#include <dto/poses/static/pose/Pose.h>
#include "dto/poses/dynamic/dynamicObject/DynamicObject.h"

class EnvSettings
{
public:
    EnvSettings(Pose start_pose, std::variant<Pose, std::shared_ptr<DynamicObject<RAPID_model>>> target,
        std::shared_ptr<RAPID_model> agent, std::vector<std::shared_ptr<RAPID_model>> obstacles,
        std::vector<std::shared_ptr<DynamicObject<RAPID_model>>> dynamic_objects,
        ConfigurationSpaceBoundaries boundaries)
        : startPose(start_pose),
          target(std::move(target)),
          agent(agent),
          obstacles(obstacles),
          dynamicObjects(dynamic_objects),
          boundaries(boundaries)
    {
    }

    Pose startPose;
    std::variant<Pose, std::shared_ptr<DynamicObject<RAPID_model>>> target;
    std::shared_ptr<RAPID_model> agent;
    std::vector<std::shared_ptr<RAPID_model>> obstacles;
    std::vector<std::shared_ptr<DynamicObject<RAPID_model>>> dynamicObjects;
    std::vector<ComponentConfig> componentConfigs;
    std::unordered_map<std::string, std::any> sharedVariables;
    ConfigurationSpaceBoundaries boundaries;
};

#endif //ENVSETTINGS_H
