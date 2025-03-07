//
// Created by arseniy on 14.1.25.
//

#ifndef BIASEDRANDOMSAMPLERFACTORY_H
#define BIASEDRANDOMSAMPLERFACTORY_H
#include "IPoseSampler.h"
#include "components/IComponentFactory.h"


class BiasedRandomSamplerFactory : public IComponentFactory<IPoseSampler>
{
public:
    std::unique_ptr<IPoseSampler> createComponent(const ComponentConfig &config, const ReaderContext &context) override;
};
#endif //BIASEDRANDOMSAMPLERFACTORY_H
