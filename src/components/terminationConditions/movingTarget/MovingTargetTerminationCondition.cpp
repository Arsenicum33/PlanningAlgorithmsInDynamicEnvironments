//
// Created by arseniy on 8.3.25.
//

#include "MovingTargetTerminationCondition.h"

bool MovingTargetTerminationCondition::isTargetReached(const Keyframe &currentPosition, const Animation &target) const
{
    Keyframe targetAtCurrentTime = target.getKeyframeAtTime(currentPosition.time);
    double distance = distanceMetric->getSpatialDistance(currentPosition, targetAtCurrentTime);
    return distance <= threshold;
}

void MovingTargetTerminationCondition::resolveDependencies(const ComponentConfig &config, ComponentManager *manager)
{
    ITerminationCondition<Keyframe, Animation>::resolveDependencies(config, manager);
    this->distanceMetric = std::dynamic_pointer_cast<ITotalDistanceMetric<Keyframe>>(manager->getComponent(ComponentType::DistanceMetric));
}
