#include "objectivestop.h"

ObjectiveStop::ObjectiveStop() {}

bool ObjectiveStop::scan(Roadmap &xmapptr, Driver *&driver, Machine *&machine, Objective *&objective)
{
    bool objectivechanged=false;
    Vec2d posvec(machine->getposx(),machine->getposy());
    Vec2d xdirvec=xmapptr.getdirection(posvec);
    Vec2d checkvec=posvec+xdirvec;
    if(xmapptr.checkifroad(checkvec))
    {
        driver->brake(machine);
    }
    else
    {
        driver->stop(machine);
    }
    return objectivechanged;
}
