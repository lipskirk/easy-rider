#ifndef MACHINE_H
#define MACHINE_H
#include "vec2d.h"

class Machine
{
protected:
    int deleteCountdown;
    float speed;
    float maxSpeed;
    float acceleration;
    float maxAcceleration;
    float minAcceleration;
    Vec2d position;

public:
    Machine();

    void countdownToDelete();
    bool checkIfToDelete();

    float getSpeed();
    float getAcceleration();
    float getPositionX();
    float getPositionY();
    float getPredictedDistance(float xtime);

    void adjustAcceleration(float xvalue);
    void moveTo(Vec2d xvec);
    float drive(Vec2d xdirvec, float xtime);

    virtual char getMachineType()=0;
    virtual void countMachineType(int vnumber[])=0;
};

#endif // MACHINE_H
