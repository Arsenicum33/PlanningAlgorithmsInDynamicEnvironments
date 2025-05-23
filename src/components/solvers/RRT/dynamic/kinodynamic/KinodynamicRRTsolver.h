// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef KINODYNAMICRRTSOLVER_H
#define KINODYNAMICRRTSOLVER_H
#include <unordered_set>

#include "AKinodynamicRRTsolver.h"
#include "dto/poses/dynamic/kinodynamic/state/State.h"


class KinodynamicRRTsolver : public AKinodynamicRRTsolver<State, Animation, Keyframe>
{
public:
    KinodynamicRRTsolver(int maxIterations, int outputPeriod, int controlInputSamples)
        : AKinodynamicRRTsolver<State, Animation, Keyframe>(
            maxIterations, outputPeriod, controlInputSamples) {}

    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);
    CapabilitySet getCapabilities() const override { return CapabilitySet{ Capability::KinodynamicEnv }; }

};



#endif //KINODYNAMICRRTSOLVER_H
