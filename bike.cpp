#include "bike.h"

Bike::Bike(Vec2d xposvec)
{
    position=xposvec;
    speed=0;
    maxSpeed=60;
    acceleration=0;
    maxAcceleration=50;
    minAcceleration=-50;
}

char Bike::getMachineType()
{
    return 'b';
}

void Bike::countMachineType(int vnumber[])
{
    vnumber[1]--;
}

