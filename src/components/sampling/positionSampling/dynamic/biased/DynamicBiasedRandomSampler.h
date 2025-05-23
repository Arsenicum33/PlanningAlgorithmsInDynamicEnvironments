// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef DYNAMICBIASEDRANDOMSAMPLER_H
#define DYNAMICBIASEDRANDOMSAMPLER_H
#include "../../ABiasedRandomSampler.h"


class DynamicBiasedRandomSampler : public ABiasedRandomSampler<Keyframe, Pose>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);
    DynamicBiasedRandomSampler(const ConfigurationSpaceBoundaries &boundaries, double goalBias)
        : ABiasedRandomSampler<Keyframe, Pose>(boundaries, goalBias) {}

    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::DynamicEnv }; }

protected:
    Keyframe sampleTarget(const Pose& target) override;

    Keyframe sampleRandom() override;
};



#endif //DYNAMICBIASEDRANDOMSAMPLER_H
