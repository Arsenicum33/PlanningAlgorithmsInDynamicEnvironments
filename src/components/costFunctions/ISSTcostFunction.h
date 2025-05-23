// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef ISSTCOSTFUNCTION_H
#define ISSTCOSTFUNCTION_H
#include <components/IComponent.h>

#include "components/solvers/SST/SSTnode.h"

template <typename StateType>
class ISSTcostFunction : public IComponent
{
public:
    virtual double getCost(std::shared_ptr<SSTnode<StateType>> parent, const StateType& currentState) = 0;

    ComponentType getType() const override { return ComponentType::CostFunction; };
};

#endif //ISSTCOSTFUNCTION_H
