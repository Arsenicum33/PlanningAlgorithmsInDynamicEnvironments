//
// Created by arseniy on 23.10.24.
//

#include "DefaultExporter.h"

#include <jsoncpp/json/value.h>
#include <fstream>
#include <dto/poses/static/pose/Pose.h>
#include <dto/poses/static/poseMath/PoseMath.h>
#include <jsoncpp/json/writer.h>

std::unique_ptr<IComponent> DefaultExporter::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    const auto& configMap = config.config;

    std::string filename = std::any_cast<std::string>(configMap.at("filename"));

    return std::make_unique<DefaultExporter>(filename);
}

Json::Value DefaultExporter::exportPositionTyped(const Pose &position, int frame) const
{
    Json::Value jsonPose;
    jsonPose["time"] = frame;

    Json::Value jsonPosition(Json::arrayValue);
    for (double coord : position.translation)
    {
        jsonPosition.append(coord);
    }
    jsonPose["position"] = jsonPosition;

    Json::Value jsonRotation(Json::arrayValue);
    std::array<double, 3> eulersAngles = PoseMath::rotationMatrixToEuler(position.rotation);
    for (double angle : eulersAngles)
    {
        jsonRotation.append(angle);
    }
    jsonPose["rotation"] = jsonRotation;

    return jsonPose;
}
