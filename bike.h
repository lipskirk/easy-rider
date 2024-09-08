#ifndef BIKE_H
#define BIKE_H
#include "machine.h"

class Bike :public Machine
{
public:
    Bike(Vec2d xposvec);
    void countMachineType(int vnumber[]) override;
    char getMachineType() override;
};

#endif // BIKE_H
