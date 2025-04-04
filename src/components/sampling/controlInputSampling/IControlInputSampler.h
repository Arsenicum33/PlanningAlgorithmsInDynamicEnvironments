//
// Created by arseniy on 20.3.25.
//

#ifndef ICONTROLINPUTSAMPLER_H
#define ICONTROLINPUTSAMPLER_H
#include "components/IComponent.h"
#include "dto/poses/dynamic/kinodynamic/controlInput/ControlInput.h"
template <typename ControlInputType, typename PositionType>
class IControlInputSampler : public IComponent
{
public:
    ComponentType getType() const override { return ComponentType::ControlInputSampler; };

    virtual ControlInputType sample(const PositionType& currentPosition) = 0;
};

#endif //ICONTROLINPUTSAMPLER_H
