//
// Created by arseniy on 14.1.25.
//

#include "BiasedRandomSamplerFactory.h"

#include "BiasedRandomSampler.h"

std::shared_ptr<IPoseSampler> BiasedRandomSamplerFactory::createComponent(ComponentConfig &config,
                                                                          ReaderContext &context)
{
    const auto& configMap = config.config;

    double goalBias = std::any_cast<double>(configMap.at("goalBias"));

    Pose goalPose = context.envSettings.endPose;

    return std::make_shared<BiasedRandomSampler>(context.envSettings.boundaries, goalBias, goalPose);
}
