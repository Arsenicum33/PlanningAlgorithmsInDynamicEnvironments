// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.

#include "StaticTerminationCondition.h"

std::unique_ptr<IComponent> StaticTerminationCondition::createComponent(const ComponentConfig &config,
                                                                        const ReaderContext &context)
{
    const auto& configMap = config.config;

    double threshold = std::any_cast<double>(configMap.at("threshold"));

    return std::make_unique<StaticTerminationCondition>(threshold);
}

void StaticTerminationCondition::resolveDependencies(const ComponentConfig &config, ComponentManager *manager)
{
    ITerminationCondition<Pose, Pose>::resolveDependencies(config, manager);
    this->distanceMetric = std::dynamic_pointer_cast<IDistanceMetric>(manager->getComponent(ComponentType::DistanceMetric));
}

double StaticTerminationCondition::computeDistance(const Pose &currentPosition, const Pose &target)
{
    return distanceMetric->getSpatialDistance(currentPosition, target);
}
