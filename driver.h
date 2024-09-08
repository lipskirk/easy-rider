#ifndef DRIVER_H
#define DRIVER_H
#include "vec2d.h"
#include "machine.h"
#include "roadmap.h"

class Driver
{
private:
    bool preferredTurnRight;
    bool isOvertaking;
    float distanceToStop;
    float distanceToObstacle;
    float distanceToOvertake;
    Vec2d crossDirection;

public:
    Driver();

    void setDistanceToStop(float xdist);
    void setDistanceToObstacle(float xdist);
    void setCrossDirection(Vec2d xvec);
    void keepDistanceToVehicleAhead(Machine *&xmachine, float xtime);
    void reduceDistanceToStop(float xchange);

    bool checkIfPreferredToTurnRight();
    bool checkIfOvertaking(Roadmap &xroadmap,Machine *&xmachine);
    float getDistanceToObstacle();
    bool checkIfCrossing();
    Vec2d getCrossDirection();
    float checkDistanceToVehicleAhead(Roadmap &xroadmap, Machine *&xmachine, float xrange);
    bool checkIfCanOvertake(Roadmap &xroadmap,Machine *&xmachine);

    void startOvertaking(Roadmap &xroadmap, Machine *&xmachine, float disttoobst);
    bool goToRoadSide(Roadmap &xroadmap, Machine *&xmachine, bool toright=false);
    void accelerate(Machine *&xmachine);
    void brake(Machine *&xmachine);
    void stop(Machine *&xmachine);
    void changeLane(Machine *&xmachine, Vec2d xvec);
    bool chooseIfTurn(float xdist, bool turnright, bool bypass=false);
    bool chooseIfJoin(float xdist, bool xturnright, bool bypass=false);
    void resetObjective();

};

#endif // DRIVER_H
