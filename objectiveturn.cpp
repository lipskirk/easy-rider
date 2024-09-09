#include "objectiveturn.h"
#include "objectiveforward.h"

ObjectiveTurn::ObjectiveTurn() {}

bool ObjectiveTurn::move(Roadmap &xmapptr, Driver *&driver, Machine *&machine, Objective *&objective, float xdist)
{
    driver->goToRoadSide(xmapptr,machine);

    Vec2d xposvec(machine->getPositionX(),machine->getPositionY());
    Vec2d xdirvec=xmapptr.getDirection(xposvec);
    Vec2d xturndirvec=xdirvec.getPerpendicular();
    if(driver->checkIfPreferredToTurnRight())
    {
        xturndirvec=xturndirvec*(-1);
    }
    Vec2d checkvec=xposvec+xturndirvec;
    if(xmapptr.checkIfDirectionSame(checkvec,xturndirvec))
    {
        Vec2d posvectmp(machine->getPositionX(),machine->getPositionY());
        xmapptr.setFree(posvectmp,true);
        driver->changeLane(machine,xturndirvec);
        posvectmp.setXY(machine->getPositionX(),machine->getPositionY());
        xmapptr.setFree(posvectmp,false);
        driver->resetObjective();
        objective=new ObjectiveForward;
        return true;
    }
    else
    {
        driver->brake(machine);
    }

    return false;
}
