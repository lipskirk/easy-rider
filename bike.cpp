#include "bike.h"

Bike::Bike(Vec2d xposvec)
{
    position=xposvec;
    speed=50;
    maxSpeed=80;
    acceleration=0;
    maxAcceleration=20;
    minAcceleration=-20;
}

void Bike::countMachineType(int vnumber[])
{
    vnumber[1]--;
}

char Bike::getMachineType()
{
    return 'b';
}
