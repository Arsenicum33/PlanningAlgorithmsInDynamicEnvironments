// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#include "StaticCollisionHandler.h"

#include <dto/poses/static/poseMath/PoseMath.h>

std::unique_ptr<IComponent> StaticCollisionHandler::createComponent(const ComponentConfig &config,
                                                                    const ReaderContext &context)
{
    return std::make_unique<StaticCollisionHandler>(context.envSettings->agent, context.envSettings->obstacles);
}

bool StaticCollisionHandler::isCollisionFree(Pose &position) const
{
    std::array<double, 3> zero_transaltion = {0, 0, 0};
    double zero_rotation[3][3] = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}};

    for (auto& obstacle : obstacles)
    {
        RAPID_Collide(PoseMath::quaternionToRotationMatrix(position.rotation).data, position.translation.data(), agent.get(), zero_rotation, zero_transaltion.data(), obstacle.get());
        if (RAPID_num_contacts > 0)
            return false;
    }

    return true;
}
