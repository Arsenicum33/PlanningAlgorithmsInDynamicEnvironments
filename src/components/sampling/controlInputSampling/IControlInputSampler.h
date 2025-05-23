// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef ICONTROLINPUTSAMPLER_H
#define ICONTROLINPUTSAMPLER_H
#include <random>

#include "components/IComponent.h"
#include "dto/poses/dynamic/kinodynamic/controlInput/ControlInput.h"
template <typename ControlInputType, typename PositionType>
class IControlInputSampler : public IComponent
{
public:
    ComponentType getType() const override { return ComponentType::ControlInputSampler; };

    virtual ControlInputType sample(const PositionType& currentPosition) = 0;

protected:
    std::mt19937 gen{std::random_device{}()};
};

#endif //ICONTROLINPUTSAMPLER_H
