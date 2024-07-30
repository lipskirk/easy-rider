#ifndef MACHINE_H
#define MACHINE_H
#include "vec2d.h"

class Machine
{
protected:
    float speed;
    float maxspeed;
    float acceleration;
    Vec2d pos;
public:
    Machine();
    void drive(Vec2d xdirvec, float xtime);
    void moveto(Vec2d xvec);
    void changespeed(float xvalue);
    float getposx();
    float getposy();
    float getspeed();
    virtual char gettype()=0;
    virtual void countup(int vnumber[])=0;
};

#endif // MACHINE_H
