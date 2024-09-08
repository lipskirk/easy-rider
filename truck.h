#ifndef TRUCK_H
#define TRUCK_H
#include"machine.h"

class Truck :public Machine
{
public:
    Truck(Vec2d xposvec);
    void countMachineType(int vnumber[]) override;
    char getMachineType() override;
};

#endif // TRUCK_H
