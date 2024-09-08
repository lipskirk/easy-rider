#include "road.h"

Road::Road(bool xfree,int xpos, int ypos,float xdir, float ydir)
{
    isFree=xfree;
    position.setXY(xpos,ypos);
    direction.setXY(xdir,ydir);
}

float Road::getPositionX()
{
    return position.getX();
}

float Road::getPositionY()
{
    return position.getY();
}

bool Road::checkIfRoad()
{
    Vec2d zerovec(0,0);
    if(direction==zerovec)
    {
        return false;
    }
    return true;
}

bool Road::checkIfFree()
{
    return isFree;
}

Vec2d Road::getDirection()
{
    return direction;
}

void Road::setFree(bool xstate)
{
    isFree=xstate;
}
