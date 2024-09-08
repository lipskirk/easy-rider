#include "driver.h"
#include "math.h"
#include <cstdlib>

Driver::Driver()
{
    preferredTurnRight=false;
    isOvertaking=false;
    distanceToObstacle=0;
    distanceToStop=0;
    distanceToOvertake=0;
    crossDirection.setXY(0,0);
}


void Driver::setDistanceToStop(float xdist)
{
    distanceToStop=xdist;
}

void Driver::setDistanceToObstacle(float xdist)
{
    distanceToObstacle=xdist;
}

void Driver::setCrossDirection(Vec2d xvec)
{
    crossDirection=xvec;
}

void Driver::keepDistanceToVehicleAhead(Machine *&xmachine, float xtime)
{
    float disttoobst;
    if(distanceToObstacle==0)
    {
        disttoobst=distanceToStop;
    }
    else if(distanceToStop==0)
    {
        disttoobst=distanceToObstacle;
    }
    else
    {
        disttoobst=std::min(distanceToObstacle,distanceToStop);
    }

    float acceleration=xmachine->getAcceleration();
    float speed=xmachine->getSpeed();

    float timetoobst=(sqrt(speed*speed+2*acceleration*disttoobst)-speed)/acceleration;
    float nt=timetoobst/xtime;

    float distance=0;

    for(int i=0;i<nt;i++)
    {
        acceleration=acceleration-1;
        distance=distance+speed*xtime+(acceleration*xtime*xtime)/2;
        speed=speed+acceleration*xtime;
    }

    if(distance>disttoobst)
    {
        brake(xmachine);
    }
}

void Driver::reduceDistanceToStop(float xchange)
{
    distanceToStop=distanceToStop-xchange;
    if(distanceToStop<0)
    {
        distanceToStop=0;
    }
}



bool Driver::checkIfPreferredToTurnRight()
{
    return preferredTurnRight;
}

bool Driver::checkIfOvertaking(Roadmap &xroadmap,Machine *&xmachine)
{
    if(isOvertaking){
        Vec2d posvec(xmachine->getPositionX(),xmachine->getPositionY());
        Vec2d dirvec=xroadmap.getDirection(posvec);

        Vec2d rightPosVec=posvec-dirvec.getPerpendicular();//pole po prawej do sprawdzenia
        float distfree=0;
        while(distfree<=distanceToOvertake+5)
        {//sprawdzenie kolejnych pól po prawej
            if(xroadmap.checkIfDirectionSame(rightPosVec,dirvec))
            {//jest prosto
                if(xroadmap.checkIfFree(rightPosVec))
                {//jest wolne, koniec wyprzedzania
                    isOvertaking=false;
                    return false;
                }
            }
            //następne pole
            distfree=distfree+1;
            rightPosVec=rightPosVec+dirvec;
        }
        return true;
    }
    return false;
}

float Driver::getDistanceToObstacle()
{
    return distanceToObstacle;
}

bool Driver::checkIfCrossing()
{
    Vec2d vec0(0,0);
    if(vec0==crossDirection)
    {
        return false;
    }
    return true;
}

Vec2d Driver::getCrossDirection()
{
    return crossDirection;
}

float Driver::checkDistanceToVehicleAhead(Roadmap &xroadmap,Machine *&xmachine, float xrange)
{
    Vec2d posvec(xmachine->getPositionX(),xmachine->getPositionY());
    Vec2d dirvec=xroadmap.getDirection(posvec);

    //szukanie przeszkod na pasie ruchu wprzod
    float xdist=0;
    Vec2d forwardPosVec=posvec;//pole na wprost do sprawdzenia
    while(
        //xroadmap.checkifroad(forwardPosVec)
        xdist<10*xrange
        )
    {//sprawdzanie kolejnych pól w przód
        xdist=xdist+1;
        forwardPosVec=forwardPosVec+dirvec;
        if(
            xroadmap.checkIfRoad(forwardPosVec)
            &&xroadmap.checkIfDirectionSame(forwardPosVec,dirvec)&&
            !xroadmap.checkIfFree(forwardPosVec))
        {//nie jest wolna
            return xdist;
        }
    }
    return 0;
}

bool Driver::checkIfCanOvertake(Roadmap &xroadmap,Machine *&xmachine)
{

    Vec2d posvec(xmachine->getPositionX(),xmachine->getPositionY());
    Vec2d dirvec=xroadmap.getDirection(posvec);

    //sprawdzenie czy może zmienić pas na lewy
    Vec2d lPosVec=posvec+dirvec.getPerpendicular();//pole po lewej do sprawdzenia

    if(!xroadmap.checkIfRoad(lPosVec)) return false;
    if(!xroadmap.checkIfDirectionSame(lPosVec,dirvec)) return false;
    if(!xroadmap.checkIfFree(lPosVec)) return false;
    if(!xroadmap.checkIfLaneEmpty(lPosVec,4)) return false;
    if(!xroadmap.checkIfLaneEmpty(lPosVec,4,true)) return false;
    return true;
}



void Driver::startOvertaking(Roadmap &xroadmap,Machine *&xmachine, float disttoobst)
{
    Vec2d posvec(xmachine->getPositionX(),xmachine->getPositionY());
    Vec2d dirvec=xroadmap.getDirection(posvec);

    Vec2d posvectmp(xmachine->getPositionX(),xmachine->getPositionY());
    xroadmap.setFree(posvectmp,true);
    changeLane(xmachine,dirvec.getPerpendicular());
    isOvertaking=true;
    distanceToOvertake=disttoobst;
    posvectmp.setXY(xmachine->getPositionX(),xmachine->getPositionY());
    xroadmap.setFree(posvectmp,true);
}

bool Driver::goToRoadSide(Roadmap &xroadmap,Machine *&xmachine, bool toright)
{
    Vec2d posvec(xmachine->getPositionX(),xmachine->getPositionY());
    Vec2d dirvec=xroadmap.getDirection(posvec);
    Vec2d turnvec=dirvec.getPerpendicular();
    if(preferredTurnRight||toright)
    {
        turnvec=turnvec*(-1);
    }

    if(xroadmap.checkIfDirectionSame(posvec+turnvec,dirvec))
    {
        if(xroadmap.checkIfFree(posvec+turnvec)
            &&xroadmap.checkIfLaneEmpty(posvec+turnvec,4)
            &&xroadmap.checkIfLaneEmpty(posvec+turnvec,4,true)
            )
        {
            changeLane(xmachine,turnvec);
        }
    }
    return true;
}

void Driver::accelerate(Machine *&xmachine)
{
    xmachine->adjustAcceleration(1);
}

void Driver::brake(Machine *&xmachine)
{
    xmachine->adjustAcceleration(-1);
}

void Driver::stop(Machine *&xmachine)
{
    xmachine->adjustAcceleration(-10000000000);
}

void Driver::changeLane(Machine *&xmachine, Vec2d xvec)
{
    xmachine->moveTo(xvec);
}


bool Driver::chooseIfTurn(float xdist, bool xturnright, bool bypass)
{
    if((rand()%4>=2)||(bypass)){
        distanceToStop=xdist;
        isOvertaking=false;
        preferredTurnRight=xturnright;
        return true;
    }
    return false;
}

bool Driver::chooseIfJoin(float xdist, bool xturnright, bool bypass)
{
    distanceToStop=xdist;
    isOvertaking=false;

    if((rand()%4>=2)||(bypass)){
        preferredTurnRight=xturnright;
        return true;
    }
    else
    {
        return false;
    }
}

void Driver::resetObjective()
{
    distanceToStop=0;
    distanceToObstacle=0;
    distanceToOvertake=0;
    if(rand()%4>=2){
        preferredTurnRight=true;//losowanie
    }
    else
    {
        preferredTurnRight=false;
    }
}
