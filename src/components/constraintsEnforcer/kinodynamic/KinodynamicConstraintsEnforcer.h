// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef CONSTRAINTSENFORCER_H
#define CONSTRAINTSENFORCER_H
#include <dto/poses/dynamic/kinodynamic/state/State.h>

#include "components/constraintsEnforcer/IConstraintsEnforcer.h"


class KinodynamicConstraintsEnforcer : public IConstraintsEnforcer<State>
{
public:
    KinodynamicConstraintsEnforcer(double maxAngularVelocity, double maxTime, double maxVelocity)
        : maxAngularVelocity(maxAngularVelocity),
          maxTime(maxTime), maxVelocity(maxVelocity) {}

    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);


    CapabilitySet getCapabilities() const override { return CapabilitySet{ Capability::KinodynamicEnv}; }

    bool satisfiesConstraints(const State &position) const override;

private:
    double maxAngularVelocity;
    double maxTime;
    double maxVelocity;
};



#endif //CONSTRAINTSENFORCER_H
