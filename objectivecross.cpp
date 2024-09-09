#include "objectivecross.h"
#include "objectiveforward.h"

ObjectiveCross::ObjectiveCross() {}

bool ObjectiveCross::move(Roadmap& xmapptr, Driver *&driver, Machine *&machine, Objective *&objective, float xdist)
{
    Vec2d posvec(machine->getPositionX(),machine->getPositionY());
    if(driver->checkIfCrossing())
    {
        if(xmapptr.checkIfDirectionSame(posvec,driver->getCrossDirection()))
        {
            Vec2d vec0(0,0);
            driver->setCrossDirection(vec0);
            objective=new ObjectiveForward;
            return true;
        }
        driver->accelerate(machine);
    }
    else
    {
        driver->goToRoadSide(xmapptr,machine,true);

        Vec2d xposvec(machine->getPositionX(),machine->getPositionY());
        Vec2d xdirvec=xmapptr.getDirection(xposvec);
        Vec2d checkvec=xposvec+xdirvec;
        if((xmapptr.checkIfDirectionSame(checkvec,xdirvec.getPerpendicular()))||(xmapptr.checkIfDirectionSame(checkvec,xdirvec.getPerpendicular()*(-1))))
        {
            if(driver->checkIfCrossRoadEmpty(xmapptr,machine))
            {
                driver->crossRoad(xmapptr,machine);
            }
            else
            {
                driver->stop(machine);
            }
        }
        else
        {
            driver->brake(machine);
        }
    }

    return false;
}
