//
// Created by arseniy on 23.10.24.
//

#ifndef ABSTRACTSOLVERCONFIG_H
#define ABSTRACTSOLVERCONFIG_H
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/json.h>
#include "../../ConfigurationSpaceBoundaries.h"
#include <stdexcept>

class AbstractSolverConfig
{
public:
    ConfigurationSpaceBoundaries boundaries;

    static AbstractSolverConfig fromJson(const Json::Value &json);
protected:
    AbstractSolverConfig(const ConfigurationSpaceBoundaries &boundaries)
    : boundaries(boundaries) {}
};



#endif //ABSTRACTSOLVERCONFIG_H
