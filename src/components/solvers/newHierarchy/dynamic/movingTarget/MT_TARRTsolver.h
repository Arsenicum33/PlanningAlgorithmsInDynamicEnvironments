//
// Created by arseniy on 17.3.25.
//

#ifndef MT_TARRT_H
#define MT_TARRT_H
#include <poses/dynamic/Animation.h>

#include "components/solvers/newHierarchy/ARRTsolver.h"


class MT_TARRTsolver : public ARRTsolver<Keyframe, Animation>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);
    MT_TARRTsolver(int maxIterations, double maxStepSize, double velocity, int outputPeriod) :
        ARRTsolver(maxIterations, maxStepSize, outputPeriod), velocity(velocity){}
    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::DynamicEnv }; }

protected:
    Keyframe getExtendedPosition(std::shared_ptr<const TreeNode<Keyframe>> neighbor, const Keyframe &sample) override;
    double velocity;
};



#endif //MT_TARRT_H
