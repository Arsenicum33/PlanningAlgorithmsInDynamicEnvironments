//
// Created by arseniy on 8.3.25.
//

#ifndef MOVINGTARGETTERMINATIONCONDITION_H
#define MOVINGTARGETTERMINATIONCONDITION_H

#include "components/distanceMeasurement/temporalTotal/ITotalDistanceMetric.h"
#include "components/interpolators/IInterpolator.h"
#include "components/interpolators/dynamic/IDynamicInterpolator.h"
#include "components/terminationConditions/ITerminationCondition.h"


class MovingTargetTerminationCondition : public ITerminationCondition<Keyframe, Animation>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);

    MovingTargetTerminationCondition(double threshold) : threshold(threshold) {}

    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::DynamicEnv, Capability::MovingTarget}; }

    bool isTargetReached(const Keyframe &currentPosition, const Animation &target) const override;

    void resolveDependencies(const ComponentConfig &config, ComponentManager *manager) override;
private:
    std::shared_ptr<ITotalDistanceMetric<Keyframe>> distanceMetric;
    std::shared_ptr<IDynamicInterpolator> interpolator;
    double threshold;
};

#endif //MOVINGTARGETTERMINATIONCONDITION_H
