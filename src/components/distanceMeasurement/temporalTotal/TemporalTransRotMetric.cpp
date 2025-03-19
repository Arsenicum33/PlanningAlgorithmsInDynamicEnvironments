//
// Created by arseniy on 10.3.25.
//

#include "TemporalTransRotMetric.h"

std::vector<double> TemporalTransRotMetric::getDimensionWeightsNoRotation() const
{
    return std::vector{1.0, 1.0, 1.0, temporalScalingFactor};
}

std::unique_ptr<IComponent> TemporalTransRotMetric::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    const auto& configMap = config.config;

    double rotationScalingFactor = std::any_cast<double>(configMap.at("rotationScalingFactor"));
    double temporalScalingFactor = std::any_cast<double>(configMap.at("temporalScalingFactor"));

    return std::make_unique<TemporalTransRotMetric>(temporalScalingFactor, rotationScalingFactor);
}

double TemporalTransRotMetric::getSpatialDistance(const Pose &pose1, const Pose &pose2)
{
    return defaultSpatialDistanceMetric.getSpatialDistance(pose1, pose2);
}

std::vector<double> TemporalTransRotMetric::getDimensionWeights() const
{
    std::vector<double> dimensionWeights = defaultSpatialDistanceMetric.getDimensionWeights();
    dimensionWeights.push_back(temporalScalingFactor);
    return dimensionWeights;
}

double TemporalTransRotMetric::getTotalDistance(const Keyframe &pos1, const Keyframe &pos2)
{
    double spatialDistance = defaultSpatialDistanceMetric.getSpatialDistance(pos1, pos2);
    double temporalDistance = std::abs((pos1.time - pos2.time) * temporalScalingFactor);
    double totalDistance = temporalDistance + spatialDistance;
    return totalDistance;
}
