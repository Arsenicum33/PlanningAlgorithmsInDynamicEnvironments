//
// Created by arseniy on 24.10.24.
//

#ifndef INPUTPARSER_H
#define INPUTPARSER_H
#include <string>
#include <stdexcept>
#include <filesystem>
#include <jsoncpp/json/json.h>
#include <fstream>
#include <dto/envSettings/EnvSettings.h>

#include "dto/envSettings/EnvSettingsAstroRaw.h"
#include "dto/envSettings/EnvSettingsRaw.h"


class InputParser
{
public:
    InputParser(int argc, char* argv[], bool useDefaultParameterValues = false);
    std::unique_ptr<EnvSettingsRaw> getEnvSettingsRaw();
private:
    void validateFilePath(const std::string& path, const std::string& fileType) const;
    std::unique_ptr<EnvSettingsRaw>  createDefaultEnvSettings();
    std::unique_ptr<EnvSettingsRaw>  createStaticEnvSettings();
    std::unique_ptr<EnvSettingsRaw>  createDynamicEnvSettings();
    std::unique_ptr<EnvSettingsRaw>  createMovingTargetEnvSettings();
    std::unique_ptr<EnvSettingsRaw>  createKinodynamicEnvSettings();
    std::unique_ptr<EnvSettingsAstroRaw>  createAstrodynamicEnvSettings();
    std::unique_ptr<EnvSettingsRaw>  createEnvSettingsFromFile(const std::string& filepath);
    std::array<double, 3> parseJsonArrayOfDoubles(const Json::Value& json);
    std::vector<std::string> parseJsonVectorOfStrings(const Json::Value& json);
    std::unordered_map<std::string, std::unordered_map<std::string, std::any>>  parseCelestialBodiesFromFile(const std::string& filepath);
    std::unordered_map<std::string, std::unordered_map<std::string, std::any>>  parseCelestialBodies(const Json::Value& json);
    std::unique_ptr<EnvSettingsRaw> envSettings;

};



#endif //INPUTPARSER_H
