//
// Created by arseniy on 15.1.25.
//

#ifndef ICOSTFUNCTION_H
#define ICOSTFUNCTION_H

#include <components/solvers/treeUtils/TreeNode.h>

#include "components/IComponent.h"

template<typename T>
class ICostFunction : public IComponent
{
public:
    virtual void apply(const TreeNode<T>& nearestNode, TreeNode<T>& newNode) = 0;
    std::string getName() const override { return "CostFunction"; };
};

#endif //ICOSTFUNCTION_H
