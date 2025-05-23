// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef FUELSTATE_H
#define FUELSTATE_H

class FuelState
{
public:
    FuelState(double main_thruster_fuel, double rotation_thrusters_fuel)
        : rotationThrustersFuel(rotation_thrusters_fuel),
          mainThrusterFuel(main_thruster_fuel) {}

    double getMainThrusterFuel() const { return mainThrusterFuel; }
    double getRotationThrustersFuel() const { return rotationThrustersFuel; }
    FuelState operator+(const FuelState &other) const
    {
        return FuelState(this->getMainThrusterFuel() + other.getMainThrusterFuel(),
            this->getRotationThrustersFuel()+other.getRotationThrustersFuel());
    }

    FuelState operator*(double factor) const
    {
        return FuelState(this->mainThrusterFuel * factor, this->rotationThrustersFuel * factor);
    }
private:
    double rotationThrustersFuel;
    double mainThrusterFuel;
};

#endif //FUELSTATE_H
