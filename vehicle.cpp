#include "vehicle.h"
#include "objectiveforward.h"

Vehicle::Vehicle(Machine *xmachineptr)
{
    driver=new Driver;
    machine=xmachineptr;
    obj=new ObjectiveForward;
}

bool Vehicle::moveVehicle(Roadmap &xmapptr, float xtime)
{
    Objective* objptrtmp=nullptr;
    if(obj->move(xmapptr,driver,machine,objptrtmp,machine->getPredictedDistance(xtime)))
    {
        obj=objptrtmp;
    }

    //zwolnienie pola dotyczasowego z xmapptr
    Vec2d posvec(machine->getPositionX(),machine->getPositionY());
    xmapptr.setFree(posvec,true);

    if(!machine->checkIfToDelete()){
        Vec2d dirvec=xmapptr.getDirection(posvec);
        if(driver->checkIfCrossing()){
            dirvec=driver->getCrossDirection();
        }
        driver->keepDistanceToVehicleAhead(machine,xtime);
        driver->reduceDistanceToStop(machine->drive(dirvec,xtime));

        //sprawdzenie czy nowa pozycja miesci sie w mapie
        posvec.setXY(machine->getPositionX(),machine->getPositionY());
        if(xmapptr.checkIfInBounds(posvec))
        {
            //jesli tak to zajecie pola w nowej pozycji
            xmapptr.setFree(posvec,false);
            return true;
        }
    }
    return false;
}

Machine* Vehicle::getMachinePtr()
{
    return machine;
}


