//
// Created by arseniy on 1.4.25.
//

#ifndef CELESTIALBODY_H
#define CELESTIALBODY_H
#include <dto/poses/dynamic/dynamicObject/DynamicObject.h>


class CelestialBody : public DynamicObject<RAPID_model>
{
public:
    CelestialBody(std::shared_ptr<Animation> animation, std::shared_ptr<RAPID_model> mesh,
        long double mass, std::string name)
        : DynamicObject<RAPID_model>(animation, mesh),
          mass(mass), name(name) {}

    unsigned long long getMass() const { return mass; };
private:
    long double mass;
    std::string name;
};



#endif //CELESTIALBODY_H
