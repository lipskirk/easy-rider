#include "bike.h"

Bike::Bike(Vec2d xposvec)
{
    pos=xposvec;
    speed=50;
    maxspeed=80;
    acceleration=1;
}

void Bike::countup(int vnumber[])
{
    vnumber[1]--;
}

char Bike::gettype()
{
    return 'b';
}
