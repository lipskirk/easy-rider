#include "machine.h"

Machine::Machine() {}

void Machine::drive(Vec2d xdirvec, float xtime)
{
    pos=pos+(xdirvec*(speed*xtime));
}

void Machine::moveto(Vec2d xvec)
{
    pos=pos+xvec;
}

void Machine::changespeed(float xvalue)
{
    xvalue=xvalue*acceleration;
    if(speed+xvalue>maxspeed)
    {
        speed=maxspeed;
    }
    else if(speed+xvalue<0)
    {
        speed=0;
    }
    else
    {
        speed=speed+xvalue;
    }
}

float Machine::getspeed()
{
    return speed;
}

float Machine::getposx()
{
    return pos.getx();
}

float Machine::getposy()
{
    return pos.gety();
}
