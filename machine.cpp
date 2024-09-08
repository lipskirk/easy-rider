#include "machine.h"

Machine::Machine()
{
    deleteCountdown=10;
}


void Machine::countdownToDelete()
{
    deleteCountdown--;
}

bool Machine::checkIfToDelete()
{
    if(deleteCountdown<=0)
    {
        return true;
    }
    return false;
}


float Machine::getSpeed()
{
    return speed;
}

float Machine::getAcceleration()
{
    return acceleration;
}

float Machine::getPositionX()
{
    return position.getX();
}

float Machine::getPositionY()
{
    return position.getY();
}

float Machine::getPredictedDistance(float xtime)
{
    float distance=(speed*xtime+acceleration*xtime*xtime);
    if(distance<0){
        return 0;
    }
    return 10*distance;
}


void Machine::adjustAcceleration(float xvalue)
{
    acceleration=acceleration+xvalue;
    if(acceleration>maxAcceleration)
    {
        acceleration=maxAcceleration;
    }
    if(acceleration<minAcceleration)
    {
        acceleration=minAcceleration;
    }
}

void Machine::moveTo(Vec2d xvec)
{
    position=position+xvec;
}

float Machine::drive(Vec2d xdirvec, float xtime)
{
    float distance=(speed*xtime+acceleration*xtime*xtime);

    if(distance<0)
    {
        distance=0;
        speed=0;
        acceleration=0;
    }

    position=position+xdirvec*distance;
    speed=speed+acceleration*xtime;
    if(speed>maxSpeed)
    {
        speed=maxSpeed;
    }
    if(speed<0)
    {
        speed=0;
    }
    return distance;
}
