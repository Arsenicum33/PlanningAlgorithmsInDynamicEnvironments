//
// Created by arseniy on 20.3.25.
//

#ifndef KINODYNAMICRRTSOLVER_H
#define KINODYNAMICRRTSOLVER_H
#include <unordered_set>

#include "AKinodynamicRRTsolver.h"
#include "dto/poses/dynamic/kinodynamic/state/State.h"


class KinodynamicRRTsolver : public AKinodynamicRRTsolver<State, Animation, Keyframe, ControlInput>
{
public:
    KinodynamicRRTsolver(int maxIterations, int outputPeriod, int controlInputSamples)
        : AKinodynamicRRTsolver<State, Animation, Keyframe, ControlInput>(
            maxIterations, outputPeriod, controlInputSamples) {}

    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);
    CapabilitySet getCapabilities() const override { return CapabilitySet{ Capability::KinodynamicEnv }; }

protected:
    std::shared_ptr<TreeNode<State>> findNearestNeighbour(const Keyframe &sample) override;
    std::shared_ptr<TreeNode<State>> chooseBestState(const std::unordered_set<std::shared_ptr<TreeNode<State>>>& nodes, const Keyframe &sample);

};



#endif //KINODYNAMICRRTSOLVER_H
