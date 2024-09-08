#include "truck.h"

Truck::Truck(Vec2d xposvec)
{
    position=xposvec;
    speed=10;
    maxSpeed=30;
    acceleration=0;
    maxAcceleration=5;
    minAcceleration=-10;
}

void Truck::countMachineType(int vnumber[])
{
    vnumber[2]--;
}

char Truck::getMachineType()
{
    return 't';
}
