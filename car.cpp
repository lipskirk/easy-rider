#include "car.h"

Car::Car(Vec2d xposvec)
{
    position=xposvec;
    speed=30;
    maxSpeed=30;
    acceleration=0;
    maxAcceleration=10;
    minAcceleration=-10;
}

void Car::countMachineType(int vnumber[])
{
    vnumber[0]--;
}

char Car::getMachineType()
{
    return 'c';
}
