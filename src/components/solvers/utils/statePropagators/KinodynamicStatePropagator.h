// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.

#ifndef STATE_BURSTCONTROLINPUT_STATEPROPAGATOR_H
#define STATE_BURSTCONTROLINPUT_STATEPROPAGATOR_H
#include <dto/poses/dynamic/kinodynamic/state/State.h>

#include "StatePropagator.h"
#include "dto/poses/dynamic/kinodynamic/burstControlInput/BurstControlInput.h"

class KinodynamicStatePropagator : public StatePropagator<State>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);
    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::KinodynamicEnv}; }
};

inline std::unique_ptr<IComponent> KinodynamicStatePropagator::createComponent(
    const ComponentConfig &config, const ReaderContext &context)
{
    return std::make_unique<KinodynamicStatePropagator>();
}
#endif //STATE_BURSTCONTROLINPUT_STATEPROPAGATOR_H
