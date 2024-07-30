#include "objectiveturn.h"
#include "objectiveforward.h"

ObjectiveTurn::ObjectiveTurn() {}

bool ObjectiveTurn::scan(Roadmap &xmapptr, Driver *&driver, Machine *&machine, Objective *&objective)
{
    bool objectivechanged=false;
    float xrange=(machine->getspeed())/2;
    Vec2d xposvec(machine->getposx(),machine->getposy());
    Vec2d xdirvec=xmapptr.getdirection(xposvec);
    Vec2d xturndirvec=xdirvec.perpendicular();
    if(driver->checkifturnright())
    {
        xturndirvec=xturndirvec*(-1);
    }
    xposvec=xposvec+xturndirvec;//pole z boku do sprawdzenia
    if(xmapptr.checkifroad(xposvec))
    {//jest drogą
        if(xmapptr.checkifdirection(xposvec,xdirvec))
        {//jest prosto
            if((xmapptr.checkiffree(xposvec))
                &&(xmapptr.checkiflanefree(xposvec,xrange))
                &&(xmapptr.checkiflanefree(xposvec,xrange,true)))
            {
                //to jako zmiana pasa przez drivera?------
                Vec2d posvectmp(machine->getposx(),machine->getposy());
                xmapptr.setfree(posvectmp,true);
                //roads[static_cast<int>(elem->getposy())*mapwidth+static_cast<int>(elem->getposx())]->makefree();
                driver->changelane(machine,xturndirvec);
                posvectmp.setxy(machine->getposx(),machine->getposy());
                xmapptr.setfree(posvectmp,false);
                //roads[static_cast<int>(elem->getposy())*mapwidth+static_cast<int>(elem->getposx())]->makeoccupied();
                //--------------------------
            }
            else
            {//jest zajęta
                //ZWOLNIJ
                driver->brake(machine);
            }
        }
        else
        {//nie jest prosto
            if(xmapptr.checkifdirection(xposvec,xturndirvec))
            {//jest w prawo
                //SKRĘĆ

                //to jako skret przez drivera?------
                Vec2d posvectmp(machine->getposx(),machine->getposy());
                xmapptr.setfree(posvectmp,true);
                //roads[static_cast<int>(elem->getposy())*mapwidth+static_cast<int>(elem->getposx())]->makefree();
                driver->changelane(machine,xturndirvec);
                posvectmp.setxy(machine->getposx(),machine->getposy());
                xmapptr.setfree(posvectmp,false);
                //roads[static_cast<int>(elem->getposy())*mapwidth+static_cast<int>(elem->getposx())]->makeoccupied();
                driver->resetdirection();
                objective=new ObjectiveForward;
                objectivechanged=true;
                //--------------------------------
            }
            else
            {//nie jest w prawo
                //ZWOLNIJ
                driver->brake(machine);
            }
        }
    }
    else
    {//nie jest drogą
        //ZWOLNIJ
        driver->brake(machine);
    }
    return objectivechanged;
}
