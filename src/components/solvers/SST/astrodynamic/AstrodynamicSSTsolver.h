// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef ASTRODYNAMICSSTSOLVER_H
#define ASTRODYNAMICSSTSOLVER_H

#include "../ASSTsolver.h"
#include "dto/poses/astrodynamic/celestialBody/CelestialBody.h"

class AstrodynamicSSTsolver : public ASSTsolver<SpaceshipState, CelestialBody>
{
public:
    AstrodynamicSSTsolver(int maxIterations, double selectionRadius, double maxWitnessProximityRadius)
        : ASSTsolver<SpaceshipState, CelestialBody>(
            maxIterations, selectionRadius, maxWitnessProximityRadius)
    {}
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);

    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::AstrodynamicEnv}; }
};


#endif //ASTRODYNAMICSSTSOLVER_H
