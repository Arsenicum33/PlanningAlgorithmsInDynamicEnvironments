// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.

#ifndef ASTRODYNAMICRRTSOLVER_H
#define ASTRODYNAMICRRTSOLVER_H
#include <components/solvers/RRT/dynamic/kinodynamic/AKinodynamicRRTsolver.h>

#include "dto/poses/astrodynamic/celestialBody/CelestialBody.h"
#include "dto/poses/astrodynamic/spaceshipState/SpaceshipState.h"

class AstrodynamicRRTsolver : public AKinodynamicRRTsolver<SpaceshipState, CelestialBody, Keyframe>
{
public:
    AstrodynamicRRTsolver(int maxIterations, int outputPeriod, int controlInputSamples)
     : AKinodynamicRRTsolver<SpaceshipState, CelestialBody, Keyframe>(
         maxIterations, outputPeriod, controlInputSamples)
    {
    }

    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);
    CapabilitySet getCapabilities() const override { return CapabilitySet{ Capability::AstrodynamicEnv }; }

};
#endif //ASTRODYNAMICRRTSOLVER_H
