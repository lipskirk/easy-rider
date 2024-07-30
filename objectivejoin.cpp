#include "objectivejoin.h"
#include "objectiveforward.h"

ObjectiveJoin::ObjectiveJoin() {}

bool ObjectiveJoin::scan(Roadmap &xmapptr, Driver *&driver, Machine *&machine, Objective *&objective)
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
            if(xmapptr.checkiffree(xposvec)
                &&(xmapptr.checkiflanefree(xposvec,xrange))
                &&(xmapptr.checkiflanefree(xposvec,xrange,true)))
            {
                //to jako zmiana pasa przed drivera?------
                Vec2d posvectmp(machine->getposx(),machine->getposy());
                xmapptr.setfree(posvectmp,true);
                //roads[static_cast<int>(elem->getposy())*mapwidth+static_cast<int>(elem->getposx())]->makefree();
                driver->changelane(machine,xturndirvec);
                posvectmp.setxy(machine->getposx(),machine->getposy());
                xmapptr.setfree(posvectmp,true);
                //roads[static_cast<int>(elem->getposy())*mapwidth+static_cast<int>(elem->getposx())]->makeoccupied();
                //------------------
            }
        }
    }
    //ZWOLNIJ
    driver->brake(machine);
    xposvec=xposvec-xturndirvec;
    xposvec=xposvec+xdirvec;//pole z przodu do sprawdzenia
    if(xmapptr.checkifdirection(xposvec,xturndirvec))
    {
        bool free=true;
        while(xmapptr.checkifdirection(xposvec,xturndirvec))
        {
            //elem->stop();
            float n=0;
            Vec2d checkvec=xposvec;
            while(n<=10){
                checkvec=checkvec+xturndirvec;
                n=n+1;
                if(xmapptr.checkifroad(checkvec)
                    &&xmapptr.checkifdirection(checkvec,xturndirvec)
                    &&(!xmapptr.checkiffree(checkvec)))
                {
                    free=false;
                    break;
                }
            }
            if(free)
            {
                checkvec=xposvec;
                n=0;
                while(n<=10){
                    checkvec=checkvec-xturndirvec;
                    n=n+1;
                    if(xmapptr.checkifroad(checkvec)
                        &&xmapptr.checkifdirection(checkvec,xturndirvec)
                        &&(!xmapptr.checkiffree(checkvec)))
                    {
                        free=false;
                        break;
                    }
                }
            }
            xposvec=xposvec+xdirvec;//kolejne pole z przodu do sprawdzenia
        }
        if(free)
        {
            //to jako wlaczenie do ruchu przed drivera?------
            Vec2d posvectmp(machine->getposx(),machine->getposy());
            xmapptr.setfree(posvectmp,true);
            //roads[static_cast<int>(elem->getposy())*mapwidth+static_cast<int>(elem->getposx())]->makefree();
            driver->join(machine,xdirvec);
            posvectmp.setxy(machine->getposx(),machine->getposy());
            xmapptr.setfree(posvectmp,true);
            //roads[static_cast<int>(elem->getposy())*mapwidth+static_cast<int>(elem->getposx())]->makeoccupied();
            driver->resetdirection();
            objective=new ObjectiveForward;
            objectivechanged=true;
            //---------------------
        }
        else
        {
            driver->stop(machine);
        }
    }
    return objectivechanged;
}
