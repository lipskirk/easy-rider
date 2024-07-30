#include "driver.h"
#include <cstdlib>

Driver::Driver()
{
    turnright=false;
    isovertaking=false;
    disttoobstacle=0;
    disttoturn=0;
    disttoovertake=0;
}

bool Driver::checkifturnright()
{
    return turnright;
}

bool Driver::checkifovertaking()
{
    return isovertaking;
}

float Driver::getdisttoturn()
{
    return disttoturn;
}

float Driver::getdisttoobstacle()
{
    return disttoobstacle;
}

float Driver::getdisttoovertake()
{
    return disttoovertake;
}


void Driver::setturnright(bool xdir)
{
    turnright=xdir;
}

void Driver::startovertaking()
{
    isovertaking=true;
}

void Driver::overtakingdone()
{
    isovertaking=false;
}

void Driver::setdisttoturn(float xdist)
{
    disttoturn=xdist;
}

void Driver::setdisttoobstacle(float xdist)
{
    disttoobstacle=xdist;
}

void Driver::setdisttoovertake(float xdist)
{
    disttoovertake=xdist;
}



void Driver::accelerate(Machine* &xmachine)
{
    xmachine->changespeed(1);
}

void Driver::brake(Machine *&xmachine)
{
    xmachine->changespeed(-3);
}

void Driver::stop(Machine* &xmachine)
{
    xmachine->changespeed(-10000);
}

void Driver::changelane(Machine *&xmachine, Vec2d xvec)
{
    xmachine->moveto(xvec);
}

void Driver::join(Machine* &xmachine, Vec2d xvec)
{
    xmachine->moveto(xvec);
}

void Driver::setistostop(float xdist)
{
    disttoturn=xdist;
}

bool Driver::chooseifturn(float xdist, bool xturnright, bool bypass)
{
    if((rand()%4>=2)||(bypass)){
        disttoturn=xdist;
        isovertaking=false;
        turnright=xturnright;
        return true;
    }
    return false;
}

bool Driver::chooseifjoin(float xdist, bool xturnright, bool bypass)
{
    if((rand()%4>=2)||(bypass)){
        disttoturn=xdist;
        isovertaking=false;
        turnright=xturnright;
        return true;
    }
    else
    {
        disttoturn=xdist;
        isovertaking=false;
        return false;
    }
}

void Driver::resetdirection()
{
    disttoturn=0;
    if(rand()%4>=2){
        turnright=true;//losowanie
    }
    else
    {
        turnright=false;
    }
}
