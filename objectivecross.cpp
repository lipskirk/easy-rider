#include "objectivecross.h"
#include "objectiveforward.h"

ObjectiveCross::ObjectiveCross() {}

bool ObjectiveCross::scan(Roadmap& xmapptr, Driver *&driver, Machine *&machine, Objective *&objective)
{
    bool objectivechanged=false;
    Vec2d xposvec(machine->getposx(),machine->getposy());
    Vec2d nowpos=xposvec;
    Vec2d xdirvec=xmapptr.getdirection(xposvec);
    driver->brake(machine);
    xposvec=xposvec+xdirvec;//pole z przodu do sprawdzenia
    bool free=true;
    if(xmapptr.checkifdirection(xposvec,xdirvec.perpendicular())||xmapptr.checkifdirection(xposvec,xdirvec.perpendicular()*(-1)))
    {
        while(xmapptr.checkifdirection(xposvec,xdirvec.perpendicular())||xmapptr.checkifdirection(xposvec,xdirvec.perpendicular()*(-1)))
        {
            float n=0;
            Vec2d checkvec=xposvec;
            while(n<=10){
                checkvec=checkvec+xdirvec.perpendicular();
                n=n+1;
                if(xmapptr.checkifroad(checkvec)
                    &&(xmapptr.checkifdirection(checkvec,xdirvec.perpendicular())||xmapptr.checkifdirection(checkvec,xdirvec.perpendicular()*(-1)))
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
                    checkvec=checkvec-xdirvec.perpendicular();
                    n=n+1;
                    if(xmapptr.checkifroad(checkvec)
                        &&(xmapptr.checkifdirection(checkvec,xdirvec.perpendicular())||xmapptr.checkifdirection(checkvec,xdirvec.perpendicular()*(-1)))
                        &&(!xmapptr.checkiffree(checkvec)))
                    {
                        free=false;
                        break;
                    }
                }
            }
            if(!free)
            {
                break;
            }
            xposvec=xposvec+xdirvec;
        }
        if(free)
        {
            //to jako przejazd przecznicy przed drivera?------
            Vec2d posvectmp(machine->getposx(),machine->getposy());
            xmapptr.setfree(posvectmp,true);
            driver->changelane(machine,xposvec-nowpos);
            posvectmp.setxy(machine->getposx(),machine->getposy());
            xmapptr.setfree(posvectmp,false);
            driver->resetdirection();
            objective=new ObjectiveForward;
            objectivechanged=true;
            //--------------------
        }
        else
        {
            driver->stop(machine);
        }
    }
    return objectivechanged;
}
