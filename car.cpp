#include "car.h"

Car::Car(Vec2d xposvec)
{
    pos=xposvec;
    speed=30;
    maxspeed=50;
    acceleration=0.5;
}

void Car::countup(int vnumber[])
{
    vnumber[0]--;
}

char Car::gettype()
{
    return 'c';
}
