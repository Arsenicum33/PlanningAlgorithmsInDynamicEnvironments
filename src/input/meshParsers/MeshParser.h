//
// Created by arseniy on 23.9.24.
//

#ifndef MESHPARSER_H
#define MESHPARSER_H
#include <memory>
#include <RAPID.H>
#include <string>
#include <vector>

template <typename MeshType>
class MeshParser
{
public:
    virtual ~MeshParser() = default;
    virtual std::vector<std::shared_ptr<MeshType>> parse(const std::string& filename) = 0;
};


#endif //MESHPARSER_H
