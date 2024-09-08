#ifndef ROAD_H
#define ROAD_H
#include "vec2d.h"

class Road
{
private:
    bool isFree;
    Vec2d direction;
    Vec2d position;
public:
    Road(bool xocc, int xpos, int ypos, float xdir, float ydir);
    float getPositionX();
    float getPositionY();
    bool checkIfRoad();
    bool checkIfFree();
    Vec2d getDirection();
    void setFree(bool xstate);
};

#endif // ROAD_H
