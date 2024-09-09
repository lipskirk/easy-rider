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
        if(!driver->checkIfOvertaking(xmapptr,machine))
        {
            driver->goToRoadSide(xmapptr,machine,true);
        }

        float disttoobst=driver->checkDistanceToVehicleAhead(xmapptr,machine,xdist);
        if(disttoobst>0)
        {
            if(disttoobst<driver->getDistanceToObstacle())
            {
                if(driver->checkIfCanOvertake(xmapptr,machine))
                {
                    driver->startOvertaking(xmapptr,machine,disttoobst);
                    disttoobst=driver->checkDistanceToVehicleAhead(xmapptr,machine,xdist);
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
        {
            driver->accelerate(machine);
        }
        driver->setDistanceToObstacle(disttoobst);

        return false;
    }
    return true; 
}

bool ObjectiveForward::checkIfRoadStraight(Roadmap &xmapptr, Driver *&driver, Machine *&machine, Objective *&objective, float xdist)
{
    float xrange=xdist;
    Vec2d xposvec(machine->getPositionX(),machine->getPositionY());
    bool right=driver->checkIfPreferredToTurnRight();
    Vec2d xdirvec=xmapptr.getDirection(xposvec);
    Vec2d xturndirvec=xdirvec.getPerpendicular();
    if(right)
    {
        xturndirvec=xturndirvec*(-1);
    }

    float disttoturn=0;
    xposvec=xposvec+xturndirvec;

    do
    {
        if(xmapptr.checkIfRoad(xposvec))
        {
            if(xmapptr.checkIfDirectionSame(xposvec,xdirvec))
            {
                xposvec=xposvec+xturndirvec;
            }
            else if(xmapptr.checkIfDirectionSame(xposvec,xdirvec*(-1)))
            {
                break;
            }
            else
            {
                xposvec=xposvec+xdirvec;
                disttoturn=disttoturn+1;
            }
        }
        else
        {
            break;
        }
    }
    while(disttoturn<xrange);

    do
    {
        if(xmapptr.checkIfRoad(xposvec))
        {
            if(xmapptr.checkIfDirectionSame(xposvec,xdirvec))
            {
                xposvec=xposvec+xturndirvec;
            }
            else if(xmapptr.checkIfDirectionSame(xposvec,xdirvec*(-1)))
            {
                xposvec=xposvec+xdirvec;
                disttoturn=disttoturn+1;
            }
            else
            {
                break;
            }
        }
        else
        {
            xposvec=xposvec+xdirvec;
            disttoturn=disttoturn+1;
        }
    }
    while(disttoturn<xrange);

    Vec2d xposvec2=xposvec-xturndirvec;
    while(!xmapptr.checkIfRoad(xposvec2))
    {
        xposvec2=xposvec2-xdirvec;
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
    {
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
    {
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
