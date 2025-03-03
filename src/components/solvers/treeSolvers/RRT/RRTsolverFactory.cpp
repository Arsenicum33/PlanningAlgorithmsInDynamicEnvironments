//
// Created by arseniy on 14.1.25.
//

#include "RRTsolverFactory.h"

std::unique_ptr<IStaticSolver> RRTsolverFactory::createComponent(const ComponentConfig &config, const ReaderContext &context)
{
    const auto& configMap = config.config;

    int maxIterations = std::any_cast<double>(configMap.at("maxIterations"));
    double maxStepSize = std::any_cast<double>(configMap.at("maxStepSize"));
    double interpolationDistanceThreshold = std::any_cast<double>(configMap.at("interpolationDistanceThreshold"));
    double interpolationRotationDistanceThreshold = std::any_cast<double>(configMap.at("interpolationRotationDistanceThreshold"));
    double rotationScalingFactor = std::any_cast<double>(configMap.at("rotationScalingFactor"));

    RRTsolverConfig solverConfig(
           maxIterations,
           maxStepSize,
           interpolationDistanceThreshold,
           interpolationRotationDistanceThreshold,
           rotationScalingFactor
       );

    return std::make_unique<RRTsolver>(solverConfig, context.envSettings);
}
