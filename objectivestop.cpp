#include "objectivestop.h"

ObjectiveStop::ObjectiveStop() {}

bool ObjectiveStop::move(Roadmap &xmapptr, Driver *&driver, Machine *&machine, Objective *&objective, float xdist)
{
    bool objectivechanged=false;

    driver->goToRoadSide(xmapptr,machine,true);

    Vec2d xposvec(machine->getPositionX(),machine->getPositionY());
    Vec2d xdirvec=xmapptr.getDirection(xposvec);
    Vec2d checkvec=xposvec+xdirvec;
    if(xmapptr.checkIfRoad(checkvec))
    {
        driver->brake(machine);
    }
    else if(xmapptr.checkIfInBounds(checkvec))
    {
        driver->stop(machine);
        machine->countdownToDelete();
    }

    return objectivechanged;
}
