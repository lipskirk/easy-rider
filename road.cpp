#include "road.h"

Road::Road(bool xfree,int xpos, int ypos,float xdir, float ydir)
{
    free=xfree;
    position.setxy(xpos,ypos);
    direction.setxy(xdir,ydir);
}

void Road::setfree(bool xstate)
{
    free=xstate;
}

float Road::getposx()
{
    return position.getx();
}

float Road::getposy()
{
    return position.gety();
}

bool Road::checkifroad()
{
    Vec2d zerovec(0,0);
    if(direction==zerovec)
    {
        return false;
    }
    return true;
}

bool Road::checkiffree()
{
    return free;
}

Vec2d Road::getdirection()
{
    return direction;
}
