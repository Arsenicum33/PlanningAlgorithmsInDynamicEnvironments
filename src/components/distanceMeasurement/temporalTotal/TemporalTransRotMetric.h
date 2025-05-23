// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef TEMPORALTRANSROTMETRIC_H
#define TEMPORALTRANSROTMETRIC_H
#include "ITotalDistanceMetric.h"
#include "components/distanceMeasurement/defaultSpatial/DefaultSpatialDistanceMetric.h"


class TemporalTransRotMetric : public ITotalDistanceMetric<Keyframe>
{
public:

    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);

    TemporalTransRotMetric(double temporalScalingFactor, double rotationScalingFactor) :
        defaultSpatialDistanceMetric(rotationScalingFactor), temporalScalingFactor(temporalScalingFactor) {}

    double getSpatialDistance(const Pose &pose1, const Pose &pose2) override;

    std::vector<double> getDimensionWeights() const override;

    double getTotalDistance(const Keyframe &pos1, const Keyframe &pos2) override;

    std::vector<double> getDimensionWeightsNoRotation() const override;

    CapabilitySet getCapabilities() const override {return CapabilitySet{Capability::StaticEnv, Capability::DynamicEnv,
        Capability::MovingTarget, Capability::KinodynamicEnv, Capability::AstrodynamicEnv};};

protected:
    DefaultSpatialDistanceMetric defaultSpatialDistanceMetric;
    double temporalScalingFactor;
};



#endif //TEMPORALTRANSROTMETRIC_H
