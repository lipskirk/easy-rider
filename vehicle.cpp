#include "vehicle.h"
#include "objectiveforward.h"

Vehicle::Vehicle(Machine *xmachineptr)
{
    driver=new Driver;
    machine=xmachineptr;
    obj=new ObjectiveForward;
}

void Vehicle::lookaround(Roadmap &xmapptr)
{
    Objective* objptrtmp=nullptr;
    if(obj->scan(xmapptr,driver,machine,objptrtmp))
    {
        obj=objptrtmp;
    }
}

bool Vehicle::move(Roadmap &xmapptr, float xtime)
{
    //zwolnieie pola dotyczasowego z xmapptr
    Vec2d posvec(machine->getposx(),machine->getposy());
    xmapptr.setfree(posvec,true);

    //przesuniecie wynikajace z parametrow pojazu i czasu
    machine->drive(xmapptr.getdirection(posvec),xtime);

    //sprawdzenie czy nowa pozycja miesci sie w mapie
    posvec.setxy(machine->getposx(),machine->getposy());
    if(xmapptr.checkifinbound(posvec))
    {
        //jesli tak to zajecie pola w nowej pozycji
        xmapptr.setfree(posvec,false);
        return true;
    }
    return false;
}

Machine* Vehicle::getmachine()
{
    return machine;
}

Objective* Vehicle::getobjective()
{
    return obj;
}


