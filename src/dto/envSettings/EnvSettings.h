// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef ENVSETTINGS_H
#define ENVSETTINGS_H
#include <RAPID.H>
#include <variant>
#include <dto/configurationSpaceBoundaries/ConfigurationSpaceBoundaries.h>
#include <dto/poses/static/pose/Pose.h>
#include <input/componentsParser/ComponentsParser.h>

#include "dto/poses/dynamic/dynamicObject/DynamicObject.h"

class EnvSettings
{
public:
    virtual ~EnvSettings() = default;
    EnvSettings(std::shared_ptr<Pose> start, std::any target,
        std::shared_ptr<RAPID_model> agent, std::vector<std::shared_ptr<RAPID_model>> obstacles,
        std::vector<std::shared_ptr<DynamicObject<RAPID_model>>> dynamic_objects,
        ConfigurationSpaceBoundaries boundaries)
        : start(start),
          target(target),
          agent(agent),
          obstacles(obstacles),
          dynamicObjects(dynamic_objects),
          boundaries(boundaries)
    {
    }

    std::shared_ptr<Pose> start;
    std::any target;
    std::shared_ptr<RAPID_model> agent;
    std::vector<std::shared_ptr<RAPID_model>> obstacles;
    std::vector<std::shared_ptr<DynamicObject<RAPID_model>>> dynamicObjects;
    std::unordered_map<std::string, std::any> sharedVariables;
    ConfigurationSpaceBoundaries boundaries;
};

#endif //ENVSETTINGS_H
