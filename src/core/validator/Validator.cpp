// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#include "Validator.h"

#include <spdlog/spdlog.h>

#include "components/capabilities/manager/CapabilityManager.h"
#include "components/collisionHandlers/dynamic/IDynamicCollisionHandler.h"
#include "components/collisionHandlers/static/IStaticCollisionHandler.h"

void Validator::validate(IComponentManager* componentManager, const EnvSettings& envSettings, const ExecutorOutput& executorOutput)
{
    return;
}

void Validator::validateComponents(IComponentManager *componentManager, const ReaderContext& readerContext)
{
    std::shared_ptr<CapabilityManager> capabilityManager = CapabilityManager::getInstance();
    CapabilitySet requiredCapabilities = capabilityManager->getRequiredCapabilities();
    const std::vector<std::shared_ptr<const IComponent>> components = componentManager->getComponents();
    for (auto& component : components)
    {
        CapabilitySet componentCapabilities = component->getCapabilities();
        for (auto& requiredCapability : requiredCapabilities)
        {
            if (!componentCapabilities.contains(requiredCapability))
            {
                spdlog::warn("Component {} does not support {}", component->getName(), capabilityToString(requiredCapability));
                //throw new std::runtime_error(component->getName() + "does not support required capabilities");
            }
        }
    }

    spdlog::info("Component validation successful");
}



