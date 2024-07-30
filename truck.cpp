#include "truck.h"

Truck::Truck(Vec2d xposvec)
{
    pos=xposvec;
    speed=10;
    maxspeed=30;
    acceleration=0.2;
}

void Truck::countup(int vnumber[])
{
    vnumber[2]--;
}

char Truck::gettype()
{
    return 't';
}
