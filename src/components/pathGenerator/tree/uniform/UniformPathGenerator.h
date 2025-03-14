//
// Created by arseniy on 8.11.24.
//

#ifndef UNIFORMPATHGENERATOR_H
#define UNIFORMPATHGENERATOR_H
#include "components/pathGenerator/tree/ITreePathGenerator.h"


class UniformPathGenerator : public ITreePathGenerator<Pose>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);
    UniformPathGenerator(double interpolationThreshold, double interpolationRotationThreshold, int desiredNumberOfFrames) :
                         interpolationThreshold(interpolationThreshold), interpolationRotationThreshold(interpolationRotationThreshold),
                         desiredNumberOfFrames(desiredNumberOfFrames) {}

    std::vector<Pose> generatePath(std::shared_ptr<TreeNode<Pose>> goalNode) override;
    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::StaticEnv}; }
private:
    double interpolationThreshold;
    double interpolationRotationThreshold;
    int desiredNumberOfFrames;
};



#endif //UNIFORMPATHGENERATOR_H
