#include "objectiveforward.h"
#include "objectivecross.h"
#include "objectivejoin.h"
#include "objectivestop.h"
#include "objectiveturn.h"

ObjectiveForward::ObjectiveForward() {}

bool ObjectiveForward::move(Roadmap &xmapptr, Driver *&driver, Machine *&machine, Objective *&objective, float xdist)
{
    if(checkIfRoadStraight(xmapptr,driver,machine,objective,xdist))
    {
        //sprawdzenie czy nie wyprzedzał lub skończył
        if(!driver->checkIfOvertaking(xmapptr,machine))
        {
            driver->goToRoadSide(xmapptr,machine,true);
        }

        float disttoobst=driver->checkDistanceToVehicleAhead(xmapptr,machine,xdist);
        if(disttoobst>0)
        {
            if(disttoobst<driver->getDistanceToObstacle())
            {//przeszkoda blizej niz poprzednio

                if(driver->checkIfCanOvertake(xmapptr,machine))
                {
                    //ZMIANA PASA NA LEWY, rozpoczecie wyprzedzania
                    driver->startOvertaking(xmapptr,machine,disttoobst);
                }
                else
                {
                    driver->brake(machine);
                }
            }
            if(disttoobst>driver->getDistanceToObstacle())
            {
                driver->accelerate(machine);
            }
        }
        else
        {//brak przeszkód, przyspieszanie i jazda prosto
            driver->accelerate(machine);
        }
        driver->setDistanceToObstacle(disttoobst);

        return false;
    }
    return true; 
}

bool ObjectiveForward::checkIfRoadStraight(Roadmap &xmapptr, Driver *&driver, Machine *&machine, Objective *&objective, float xdist)
{
    float xrange=5*xdist;
    Vec2d xposvec(machine->getPositionX(),machine->getPositionY());
    bool right=driver->checkIfPreferredToTurnRight();
    Vec2d xdirvec=xmapptr.getDirection(xposvec);
    Vec2d xturndirvec=xdirvec.getPerpendicular();
    if(right)
    {
        xturndirvec=xturndirvec*(-1);
    }

    float disttoturn=0;//dystans do zakretu
    xposvec=xposvec+xturndirvec;//pole z boku

    do
    {//sprawdzenie kolejnego pola
        if(xmapptr.checkIfRoad(xposvec))
        {//jest drogą
            if(xmapptr.checkIfDirectionSame(xposvec,xdirvec))
            {//jest prosto
                xposvec=xposvec+xturndirvec;//do spr. następne pole w kierunku skrętu
            }
            else if(xmapptr.checkIfDirectionSame(xposvec,xdirvec*(-1)))
            {//jest w tył
                break;
            }
            else
            {// jest w bok
                xposvec=xposvec+xdirvec;
                disttoturn=disttoturn+1;//do spr. następne pole prosto
            }
        }
        else
        {//nie jest drogą
            break;
        }
    }
    while(disttoturn<xrange);

    do
    {//sprawdzenie kolejnego pola
        if(xmapptr.checkIfRoad(xposvec))
        {//jest drogą
            if(xmapptr.checkIfDirectionSame(xposvec,xdirvec))
            {//jest prosto
                xposvec=xposvec+xturndirvec;//do spr. następne pole w kierunku skrętu
            }
            else if(xmapptr.checkIfDirectionSame(xposvec,xdirvec*(-1)))
            {//jest w tył
                xposvec=xposvec+xdirvec;
                disttoturn=disttoturn+1;//do spr. następne pole prosto
            }
            else
            {// jest w bok
                break;
            }
        }
        else
        {//nie jest drogą
            xposvec=xposvec+xdirvec;
            disttoturn=disttoturn+1;//do spr. następne pole prosto
        }
    }
    while(disttoturn<xrange);

    Vec2d xposvec2=xposvec-xturndirvec;
    while(!xmapptr.checkIfRoad(xposvec2))
    {//na wprost nie ma drogi
        xposvec2=xposvec2-xdirvec;//cofnięcie do punktu, gdzie droga się skończyła
        disttoturn=disttoturn-1;
    }
    xposvec=xposvec2+xturndirvec;

    bool fw=false;
    Vec2d xposvec3=xposvec;
    do
    {
        xposvec3=xposvec3+xdirvec;
    }
    while(xmapptr.checkIfRoad(xposvec3));

    xposvec3=xposvec3-xturndirvec;
    if(xmapptr.checkIfDirectionSame(xposvec3,xdirvec))
    {
        fw=true;
    }
    if(xmapptr.checkIfDirectionSame(xposvec2,xdirvec))
    {//nie ma przecznicy na drodze
        if(xmapptr.checkIfDirectionSame(xposvec,xturndirvec))
        {
            if(driver->chooseIfTurn(disttoturn,right,!fw))
            {
                objective=new ObjectiveTurn;
                return false;
            }
        }
        else if(!fw)
        {
            Vec2d xposvec4=xposvec2;
            while(xmapptr.checkIfDirectionSame(xposvec4,xdirvec))
            {
                xposvec4=xposvec4-xturndirvec;
            }
            if(xmapptr.checkIfDirectionSame(xposvec4,xturndirvec*(-1)))
            {
                if(driver->chooseIfTurn(disttoturn,!right,!fw))
                {
                    objective=new ObjectiveTurn;
                    return false;
                }
            }
            else if(xmapptr.checkIfInBounds(xposvec3))
            {
                driver->setDistanceToStop(disttoturn);
                objective=new ObjectiveStop;
                return false;
            }
        }
    }
    else
    {//jest przecznica na drodze
        if(!xmapptr.checkIfDirectionSame(xposvec2,xturndirvec))
        {
            right=!right;
        }
        if(driver->chooseIfJoin(disttoturn,right,!fw))
        {
            objective=new ObjectiveJoin;
        }
        else
        {
            objective=new ObjectiveCross;
        }
        return false;
    }
    return true;
}
