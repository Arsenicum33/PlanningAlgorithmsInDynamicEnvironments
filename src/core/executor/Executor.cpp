// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#include "Executor.h"
#include <spdlog/spdlog.h>

#include "components/agentModel/IAgentModel.h"
#include "components/agentModel/spacecraftModel/SpacecraftModel.h"
#include "components/capabilities/manager/CapabilityManager.h"
#include "dto/envSettings/EnvSettingsAstro.h"
#include "dto/poses/dynamic/kinodynamic/state/State.h"

ExecutorOutput Executor::run(IComponentManager* componentManager, const EnvSettings& envSettings)
{
    std::shared_ptr<CapabilityManager> capabilityManager = CapabilityManager::getInstance();
    CapabilitySet capabilities = capabilityManager->getRequiredCapabilities();
    std::shared_ptr<IComponent> solverComponent = componentManager->getComponent(ComponentType::Solver);
    try
    {
        std::shared_ptr<ISolver> solver = std::dynamic_pointer_cast<ISolver>(solverComponent);
        std::vector<std::any> path = runAppropriateSolver(solver, capabilities, envSettings, componentManager);
        int totalIterations = solver->getTotalIterations();
        int totalRuntime = solver->getTotalRuntime();
        return ExecutorOutput{ path, totalIterations, totalRuntime};
    }
    catch (std::exception& e)
    {
        spdlog::error(e.what());
        throw e;
    }
    catch (...)
    {
        spdlog::error("Caught unknown exception");
        throw;
    }
}

std::vector<std::any> Executor::runAppropriateSolver(std::shared_ptr<ISolver> solver,
    const CapabilitySet &requiredCapabilities, const EnvSettings &envSettings, IComponentManager* componentManager) const
{
    if (requiredCapabilities.contains(Capability::AstrodynamicEnv))
    {
        spdlog::info("Solving for Astrodynamic scenario");
        return runAstrodynamicSolver(solver, dynamic_cast<const EnvSettingsAstro&>(envSettings), componentManager);
    }
    if (requiredCapabilities.contains(Capability::KinodynamicEnv))
    {
        spdlog::info("Solving for Kinodynamic scenario");
        return runKinodynamicSolver(solver, envSettings);
    }
    if (requiredCapabilities.contains(Capability::MovingTarget))
    {
        spdlog::info("Solving for Moving Target scenario");
        return runMovingTargetSolver(solver, envSettings);
    }
    if (requiredCapabilities.contains(Capability::DynamicEnv))
    {
        spdlog::info("Solving for Dynamic env scenario");
        return runDynamicSolver(solver, envSettings);
    }
    if (requiredCapabilities.contains(Capability::StaticEnv))
    {
        spdlog::info("Solving for Static env scenario");
        return runStaticSolver(solver, envSettings);
    }
    spdlog::error("Executor failed to get a suitable solver");
    throw std::runtime_error("Executor failed to get a suitable solver");
}

std::vector<std::any> Executor::runMovingTargetSolver(std::shared_ptr<ISolver> solver, const EnvSettings &envSettings) const
{
    std::shared_ptr<DynamicObject<RAPID_model>> target = std::any_cast<std::shared_ptr<DynamicObject<RAPID_model> > >(
        envSettings.target);
    const Animation *targetAnimation = target->getAnimation();
    Keyframe start(*(envSettings.start.get()), 1.0);
    std::vector<std::any> result = solver->solve(start, *targetAnimation);
    return  result;
}

std::vector<std::any> Executor::runDynamicSolver(std::shared_ptr<ISolver> solver, const EnvSettings &envSettings) const
{
    Pose target = std::any_cast<Pose>(envSettings.target);
    Keyframe start(*(envSettings.start.get()), 1.0);
    std::vector<std::any> result = solver->solve(start, target);
    return  result ;
}

std::vector<std::any> Executor::runStaticSolver(std::shared_ptr<ISolver> solver, const EnvSettings &envSettings) const
{
    Pose target = std::any_cast<Pose>(envSettings.target);
    const Pose& start = *envSettings.start.get();
    std::vector<std::any> result = solver->solve(start, target);
    return result;
}

std::vector<std::any> Executor::runKinodynamicSolver(std::shared_ptr<ISolver> solver, const EnvSettings &envSettings) const
{
    std::shared_ptr<DynamicObject<RAPID_model>> target = std::any_cast<std::shared_ptr<DynamicObject<RAPID_model>>>(
        envSettings.target);
    const Animation *targetAnimation = target->getAnimation();
    Keyframe startKeyframe(*(envSettings.start.get()), 1.0);
    State start(startKeyframe, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0});
    std::vector<std::any> result = solver->solve(start, *targetAnimation);
    return result;
}

std::vector<std::any> Executor::runAstrodynamicSolver(std::shared_ptr<ISolver> solver, const EnvSettingsAstro &envSettings,
    IComponentManager* componentManager) const
{
    std::shared_ptr<CelestialBody> target = std::any_cast<std::shared_ptr<CelestialBody>>(
        envSettings.target);
    std::shared_ptr<IComponent> spacecraftModelComponent = componentManager->getComponent(ComponentType::AgentModel);
    std::shared_ptr<SpacecraftModel> spacecraftModel =
        std::dynamic_pointer_cast<SpacecraftModel>(spacecraftModelComponent);
    SpaceshipState start(*std::dynamic_pointer_cast<State>(envSettings.start).get(),
        spacecraftModel->getInitialFuel());
    std::vector<std::any> result = solver->solve(start, *target);
    return result;
}



