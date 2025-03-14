//
// Created by arseniy on 23.10.24.
//

#ifndef DEFAULTEXPORTER_H
#define DEFAULTEXPORTER_H
#include <components/exporters/AbstractExporter.h>

class DefaultExporter : public AbstractExporter<Pose>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);
    DefaultExporter(const std::string& filename) : AbstractExporter(filename) {};

    std::vector<Pose> exportPoses(std::vector<Pose>& poses) override;
    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::StaticEnv}; }
};



#endif //DEFAULTEXPORTER_H
