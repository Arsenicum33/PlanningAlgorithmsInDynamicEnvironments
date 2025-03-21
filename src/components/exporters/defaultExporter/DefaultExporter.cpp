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

void DefaultExporter::exportPositionsTyped(std::vector<Pose> positions) const
{
    Json::Value root(Json::arrayValue);  // Create a JSON array to hold poses

    // Loop through each static and serialize it to JSON
    int frameCounter = 1;
    std::array<double, 3> eulersAngles;
    for (const auto& pose : positions)
    {
        Json::Value jsonPose;
        jsonPose["time"] = frameCounter;

        // Add position (x, y, z)
        Json::Value jsonPosition(Json::arrayValue);
        for (double coord : pose.translation)
        {
            jsonPosition.append(coord);
        }
        jsonPose["position"] = jsonPosition;

        // Add rotation (rx, ry, rz)
        Json::Value jsonRotation(Json::arrayValue);
        eulersAngles = PoseMath::rotationMatrixToEuler(pose.rotation);
        for (double angle : eulersAngles)
        {
            jsonRotation.append(angle);
        }
        jsonPose["rotation"] = jsonRotation;

        // Add this static to the root array
        root.append(jsonPose);
        frameCounter++;
    }

    // Write the JSON array to the output file
    std::ofstream file(filename, std::ofstream::out);
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open file for writing: " + filename);
    }

    // Write the JSON content to the file
    Json::StreamWriterBuilder writer;
    std::unique_ptr<Json::StreamWriter> jsonWriter(writer.newStreamWriter());
    jsonWriter->write(root, &file);
    file.close();
}
