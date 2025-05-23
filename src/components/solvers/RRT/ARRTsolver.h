// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.

#ifndef ARRTSOLVER_H
#define ARRTSOLVER_H
#include "../ISolver.h"
#include "components/pathGenerator/tree/ITreePathGenerator.h"
#include "../../sampling/positionSampling/IPositionSampler.h"
#include "components/terminationConditions/ITerminationCondition.h"
#include "components/nearestNeighbour/mpnn/IMPNNsearch.h"
#include "components/solvers/ATypedSolver.h"
#include <optional>

#include "components/nearestNeighbour/mpnn/rrt/AMPNN_RRT.h"

template <typename PositionType, typename TargetType, typename SampleType>
class ARRTsolver : public ATypedSolver<PositionType, TargetType>
{
public:
    ARRTsolver(int maxIterations, int outputPeriod)
        : maxIterations(maxIterations),
          outputPeriod(outputPeriod) {}

    void resolveDependencies(const ComponentConfig &config, ComponentManager *manager) override;

    int getTotalIterations() const override;

protected:
    std::vector<PositionType> solveTyped(const PositionType& start, const TargetType& target) override;

    virtual void initialize(const PositionType& start);
    virtual void outputIteration(int currentIteration);
    virtual SampleType samplePosition(const TargetType& target);
    virtual std::shared_ptr<TreeNode<PositionType>> findNearestNeighbour(const SampleType& sample);
    virtual std::optional<std::shared_ptr<TreeNode<PositionType>>> growTowardTarget(
        std::shared_ptr<TreeNode<PositionType>> neighbour, const SampleType& sample, const TargetType& target) = 0;
    virtual bool isTargetReached(std::shared_ptr<const TreeNode<PositionType>> newNode, const TargetType& target);
    virtual std::vector<PositionType> extractPath(std::shared_ptr<const TreeNode<PositionType>> finalNode);
    virtual std::vector<PositionType> handleSolutionNotFound();

public:
    std::vector<std::shared_ptr<ANode>> getData() override;

protected:
    int maxIterations;
    int outputPeriod;
    std::shared_ptr<INearestNeighborSearch<TreeNode<PositionType>, SampleType>> nnSearch;
    std::shared_ptr<IPositionSampler<SampleType, TargetType>> positionSampler;
    std::shared_ptr<ICollisionHandler<PositionType>> collisionHandler;
    std::shared_ptr<IInterpolator<PositionType>> interpolator; //TODO remove this unnecessary dependency if kinodynamic RRT* will not justify it
    std::shared_ptr<IDistanceMetric> distanceMetric;
    std::shared_ptr<ITreePathGenerator<PositionType>> pathGenerator;
    std::shared_ptr<ITerminationCondition<PositionType, TargetType>> terminationCondition;

private:
    int totalIterations = -1;
    std::chrono::time_point<std::chrono::steady_clock> timerStart;

};

template<typename PositionType, typename TargetType, typename SampleType>
std::vector<PositionType> ARRTsolver<PositionType, TargetType, SampleType>::solveTyped(const PositionType &start,
    const TargetType &target)
{
    initialize(start);
    for (int i=0; i<maxIterations; i++)
    {
        outputIteration(i);
        SampleType sample = samplePosition(target);
        std::shared_ptr<TreeNode<PositionType>> neighbour = findNearestNeighbour(sample);
        std::optional<std::shared_ptr<TreeNode<PositionType>>> resultNode = growTowardTarget(neighbour, sample, target);
        if (resultNode.has_value() && isTargetReached(*resultNode, target))
        {
            totalIterations = i+1;
            return extractPath(*resultNode);
        }
    }
    return handleSolutionNotFound();
}

template<typename PositionType, typename TargetType, typename SampleType>
void ARRTsolver<PositionType, TargetType, SampleType>::initialize(const PositionType &start)
{
    spdlog::info("Solver started!");
    nnSearch->add(std::make_shared<TreeNode<PositionType>>(start, nullptr, 0.0));
    timerStart = std::chrono::steady_clock::now();
}

template<typename PositionType, typename TargetType, typename SampleType>
void ARRTsolver<PositionType, TargetType, SampleType>::outputIteration(int currentIteration)
{
    if ((currentIteration+1) % outputPeriod == 0)
    {
        spdlog::info("Iteration {}/{}", currentIteration+1, maxIterations);

    }
    if ((currentIteration+1) % this->dataOutputPeriod == 0)
    {
        this->iterationsToNodes.push_back(std::make_pair(currentIteration+1, this->totalNodes));
        auto total = std::chrono::steady_clock::now() - timerStart;
        int runtime =  std::chrono::duration_cast<std::chrono::milliseconds>(total).count();
        this->iterationsToRuntime.push_back(std::make_pair(currentIteration+1, runtime));
    }
}

template<typename PositionType, typename TargetType, typename SampleType>
SampleType ARRTsolver<PositionType, TargetType, SampleType>::samplePosition(const TargetType &target)
{
    return positionSampler->sample(target);
}


template<typename PositionType, typename TargetType, typename SampleType>
std::shared_ptr<TreeNode<PositionType>> ARRTsolver<PositionType, TargetType, SampleType>::findNearestNeighbour(
    const SampleType &sample)
{
    return nnSearch->findNearest(sample);
}


template<typename PositionType, typename TargetType, typename SampleType>
bool ARRTsolver<PositionType, TargetType, SampleType>::isTargetReached(std::shared_ptr<const TreeNode<PositionType>> newNode,
    const TargetType &target)
{
    return terminationCondition->isTargetReached(newNode->pose, target);
}


template<typename PositionType, typename TargetType, typename SampleType>
std::vector<PositionType> ARRTsolver<PositionType, TargetType, SampleType>::extractPath(
    std::shared_ptr<const TreeNode<PositionType>> finalNode)
{
    spdlog::info("Solution found!");
    return pathGenerator->generatePath(finalNode);
}

template<typename PositionType, typename TargetType, typename SampleType>
std::vector<PositionType> ARRTsolver<PositionType, TargetType, SampleType>::handleSolutionNotFound()
{
    totalIterations = maxIterations;
    spdlog::error("Solution NOT found!");
    throw std::runtime_error("Solution NOT found!");
}

template<typename PositionType, typename TargetType, typename SampleType>
void ARRTsolver<PositionType, TargetType, SampleType>::resolveDependencies(const ComponentConfig &config, ComponentManager *manager)
{
    ISolver::resolveDependencies(config, manager);
    nnSearch = std::dynamic_pointer_cast<INearestNeighborSearch<TreeNode<PositionType>, SampleType>>(manager->getComponent(ComponentType::NearestNeighbourSearch));
    collisionHandler = std::dynamic_pointer_cast<ICollisionHandler<PositionType>>(manager->getComponent(ComponentType::CollisionHandler));
    interpolator = std::dynamic_pointer_cast<IInterpolator<PositionType>>(manager->getComponent(ComponentType::Interpolator));
    distanceMetric = std::dynamic_pointer_cast<IDistanceMetric>(manager->getComponent(ComponentType::DistanceMetric));
    positionSampler = std::dynamic_pointer_cast<IPositionSampler<SampleType, TargetType>>(manager->getComponent(ComponentType::PositionSampler));
    pathGenerator = std::dynamic_pointer_cast<ITreePathGenerator<PositionType>>(manager->getComponent(ComponentType::PathGenerator));
    terminationCondition = std::dynamic_pointer_cast<ITerminationCondition<PositionType, TargetType>>(manager->getComponent(ComponentType::TerminationCondition));
}

template<typename PositionType, typename TargetType, typename SampleType>
int ARRTsolver<PositionType, TargetType, SampleType>::getTotalIterations() const
{
    if (totalIterations < 0)
    {
        spdlog::error("The algorithm hasnt finished, cant call getTotalIterations()");
        throw std::runtime_error("getTotalIterations() failed");
    }
    return totalIterations;
}

template<typename PositionType, typename TargetType, typename SampleType>
std::vector<std::shared_ptr<ANode>> ARRTsolver<PositionType, TargetType, SampleType>::getData()
{
    auto nodes = nnSearch->getNodes();
    std::vector<std::shared_ptr<ANode>> result;
    for (auto node : nodes)
    {
        result.push_back(node);
    }
    return result;
}


#endif //ARRTSOLVER_H
