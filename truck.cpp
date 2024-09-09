#include "truck.h"

Truck::Truck(Vec2d xposvec)
{
    position=xposvec;
    speed=0;
    maxSpeed=20;
    acceleration=0;
    maxAcceleration=10;
    minAcceleration=-10;
}

char Truck::getMachineType()
{
    return 't';
}

void Truck::countMachineType(int vnumber[])
{
    vnumber[2]--;
}
