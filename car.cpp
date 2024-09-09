#include "car.h"

Car::Car(Vec2d xposvec)
{
    position=xposvec;
    speed=0;
    maxSpeed=40;
    acceleration=0;
    maxAcceleration=30;
    minAcceleration=-30;
}

char Car::getMachineType()
{
    return 'c';
}

void Car::countMachineType(int vnumber[])
{
    vnumber[0]--;
}
