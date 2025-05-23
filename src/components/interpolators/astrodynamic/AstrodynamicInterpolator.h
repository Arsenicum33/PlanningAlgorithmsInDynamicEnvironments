// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef ASTRODYNAMICINTERPOLATOR_H
#define ASTRODYNAMICINTERPOLATOR_H
#include "components/interpolators/AInterpolator.h"
#include "dto/poses/astrodynamic/spaceshipState/SpaceshipState.h"


class AstrodynamicInterpolator : public AInterpolator<SpaceshipState>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);

    AstrodynamicInterpolator(double interpolationTimestep)
        : interpolationTimestep(interpolationTimestep) {}


    CapabilitySet getCapabilities() const override { return CapabilitySet{ Capability::AstrodynamicEnv}; }

protected:
    int calculateInterpolationSteps(const SpaceshipState &from, const SpaceshipState &to) override;

    SpaceshipState interpolateBetweenPositions(const SpaceshipState &start, const SpaceshipState &end, double factor) override;

private:
    double interpolationTimestep;

};

#endif //ASTRODYNAMICINTERPOLATOR_H
