// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef GRAVITYINTERACTION_H
#define GRAVITYINTERACTION_H
#include <vector>
#include <components/distanceMeasurement/IDistanceMetric.h>
#include <utils/AnimationUtils.h>

#include "IInteraction.h"
#include "dto/poses/astrodynamic/celestialBody/CelestialBody.h"

#define GRAVITATIONAL_CONSTANT 6.6743e-20 // G [km^3 * kg * s^(-2)]
#define DISTANCE_ZERO_TOLERANCE 1000
template <typename StateType>
class GravityInteraction : public IInteraction<StateType>
{
public:
    GravityInteraction(std::vector<CelestialBody> celestialBodies) :
        celestialBodies(celestialBodies) {}

//#ifdef UNIT_TESTING
    GravityInteraction(std::vector<CelestialBody> celestialBodies,
                       std::shared_ptr<IDistanceMetric> distanceMetric,  std::shared_ptr<IAgentModel<StateType>> spacecraft) :
        celestialBodies(celestialBodies),
        distanceMetric(distanceMetric),
    spacecraftModel(spacecraft) {}
//#endif

    TotalForce computeTotalForce(const StateType &state) override;
    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::AstrodynamicEnv}; }
    void resolveDependencies(const ComponentConfig &config, ComponentManager *manager) override;
protected:
    std::vector<CelestialBody> celestialBodies;
    std::shared_ptr<IDistanceMetric> distanceMetric;
    std::shared_ptr<IAgentModel<StateType>> spacecraftModel;
private:
    TotalForce computeForceForCelestialBody(const StateType &state, const CelestialBody &celestialBody);
};

template<typename StateType>
TotalForce GravityInteraction<StateType>::computeTotalForce(const StateType &state)
{
    TotalForce totalForce;
    for (const auto& celestialBody : celestialBodies)
    {
        TotalForce force = computeForceForCelestialBody(state, celestialBody);
        totalForce+=force;
    }
    return totalForce;
}

template<typename StateType>
void GravityInteraction<StateType>::resolveDependencies(const ComponentConfig &config, ComponentManager *manager)
{
    IInteraction<StateType>::resolveDependencies(config, manager);
    this->distanceMetric = std::dynamic_pointer_cast<IDistanceMetric>(
        manager->getComponent(ComponentType::DistanceMetric));
    this->spacecraftModel = std::dynamic_pointer_cast<IAgentModel<StateType>>(manager->getComponent(ComponentType::AgentModel));
}

template<typename StateType>
TotalForce GravityInteraction<StateType>::computeForceForCelestialBody(const StateType &state, const CelestialBody& celestialBody)
{
    using namespace PhysicsUtils;
    double m1 = spacecraftModel->getTotalMass(state);
    double m2 = celestialBody.getMass();
    Keyframe bodyKeyframe = AnimationUtils::extractKeyframeAtTime(celestialBody.getAnimation(), state.time);
    double distance = distanceMetric->getSpatialDistance(state, bodyKeyframe);
    if (distance < DISTANCE_ZERO_TOLERANCE)
    {
        spdlog::error("Distance is (almost) zero, cant compute gravitational interaction");
        throw std::runtime_error("Distance is (almost) zero, cant compute gravitational interaction");
    }
    std::array<double, 3> forceDirection = normalize(bodyKeyframe.translation - state.translation);
    std::array<double, 3> force = forceDirection * (GRAVITATIONAL_CONSTANT * m1 * m2 / distance / distance);
    return TotalForce(force, std::array<double, 3>{0, 0, 0});
}

#endif //GRAVITYINTERACTION_H
