//
// Created by arseniy on 13.1.25.
//

#include "Executor.h"

#include <components/solvers/IStaticSolver.h>

#include "components/solvers/dynamic/IDynamicSolver.h"

ExecutorOutput Executor::run(IComponentManager* componentManager, EnvSettings envSettings)
{
    std::shared_ptr<IStaticSolver> solver = std::dynamic_pointer_cast<IStaticSolver>(componentManager->getComponent("Solver"));
    std::vector<Pose> solution = solver->solve(envSettings.startPose, envSettings.endPose);
    ExecutorOutput output { solution };
    return output;
}
