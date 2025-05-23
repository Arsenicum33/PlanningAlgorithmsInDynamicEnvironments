// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef ANODE_H
#define ANODE_H
#include <memory>
#include <vector>
#include <dto/poses/static/pose/Pose.h>

class ANode
{
public:
    virtual ~ANode() = default;

    ANode()
    {
        index = indexCounter++;
    }
    int getIndex() const { return index; }

    virtual std::weak_ptr<ANode> getParent() = 0;
    virtual std::vector<std::shared_ptr<ANode>> getChildren() = 0;
    virtual const Pose* getStateRepresentation() const = 0;
private:
    int index;
    static int indexCounter;
};



#endif //ANODE_H
