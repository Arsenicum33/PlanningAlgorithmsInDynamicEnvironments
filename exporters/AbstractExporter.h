//
// Created by arseniy on 23.10.24.
//

#ifndef ABSTRACTEXPORTER_H
#define ABSTRACTEXPORTER_H

#include <string>
#include <vector>

#include "../poses/Pose.h"

class AbstractExporter
{
public:
    virtual ~AbstractExporter() = default;

    AbstractExporter(const std::string& filename) : filename(filename) {};
    virtual void exportPoses(std::vector<Pose>& poses) = 0;
protected:
    std::string filename;
};


#endif //ABSTRACTEXPORTER_H
