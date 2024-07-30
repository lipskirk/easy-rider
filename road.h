#ifndef ROAD_H
#define ROAD_H
#include "vec2d.h"

class Road
{
private:
    bool free;
    Vec2d direction;
    Vec2d position;
public:
    Road(bool xocc, int xpos, int ypos, float xdir, float ydir);
    void setfree(bool xstate);
    float getposx();
    float getposy();
    bool checkifroad();
    bool checkiffree();
    Vec2d getdirection();
};

#endif // ROAD_H
