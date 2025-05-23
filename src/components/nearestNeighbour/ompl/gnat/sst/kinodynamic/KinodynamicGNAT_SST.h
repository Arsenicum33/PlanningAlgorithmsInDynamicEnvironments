// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.

#ifndef KINODYNAMICGNAT_SST_H
#define KINODYNAMICGNAT_SST_H
#include <dto/poses/dynamic/kinodynamic/state/State.h>

#include "components/nearestNeighbour/ompl/gnat/sst/AGNAT_SST.h"


class KinodynamicGNAT_SST : public AGNAT_SST<State>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context)
    {
        return std::make_unique<KinodynamicGNAT_SST>();
    };
    CapabilitySet getCapabilities() const override { return CapabilitySet{Capability::KinodynamicEnv};}

    void build() override;

protected:
    std::shared_ptr<SSTnode<State>> searchedTypeToStoredType(const State &state) const override;
};



#endif //KINODYNAMICGNAT_SST_H
