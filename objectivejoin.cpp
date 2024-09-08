#include "objectivejoin.h"
#include "objectiveforward.h"

ObjectiveJoin::ObjectiveJoin() {}

bool ObjectiveJoin::move(Roadmap &xmapptr, Driver *&driver, Machine *&machine, Objective *&objective, float xdist)
{
    bool objectivechanged=false;

    driver->goToRoadSide(xmapptr,machine);

    Vec2d xposvec(machine->getPositionX(),machine->getPositionY());
    Vec2d xdirvec=xmapptr.getDirection(xposvec);
    Vec2d xturndirvec=xdirvec.getPerpendicular();
    if(driver->checkIfPreferredToTurnRight())
    {
        xturndirvec=xturndirvec*(-1);
    }
    Vec2d checkvec=xposvec+xdirvec;
    if(xmapptr.checkIfDirectionSame(checkvec,xturndirvec))
    {
        Vec2d posvectmp(machine->getPositionX(),machine->getPositionY());
        xmapptr.setFree(posvectmp,true);
        driver->changeLane(machine,xdirvec);
        posvectmp.setXY(machine->getPositionX(),machine->getPositionY());
        xmapptr.setFree(posvectmp,false);
        driver->resetObjective();
        objective=new ObjectiveForward;
        objectivechanged=true;
    }
    else
    {
        driver->brake(machine);
    }

    return objectivechanged;
}
