//
// Created by arseniy on 14.1.25.
//

#include "WeightedTransRotMetricFactory.h"

#include "WeightedTranslationRotationMetric.h"

std::unique_ptr<IDistanceMetric> WeightedTransRotMetricFactory::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    const auto& configMap = config.config;

    double rotationScalingFactor = std::any_cast<double>(configMap.at("rotationScalingFactor"));

    return std::make_unique<WeightedTranslationRotationMetric>(rotationScalingFactor);
}
