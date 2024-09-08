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
            bool free=true;

            while(xmapptr.checkIfDirectionSame(xposvec,xdirvec.getPerpendicular())||xmapptr.checkIfDirectionSame(xposvec,xdirvec.getPerpendicular()*(-1)))
            {
                float n=0;
                Vec2d checkvec=xposvec;
                while(n<=10){
                    checkvec=checkvec+xdirvec.getPerpendicular();
                    n=n+1;
                    if(xmapptr.checkIfRoad(checkvec)
                        &&(xmapptr.checkIfDirectionSame(checkvec,xdirvec.getPerpendicular())||xmapptr.checkIfDirectionSame(checkvec,xdirvec.getPerpendicular()*(-1)))
                        &&(!xmapptr.checkIfFree(checkvec)))
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
                        checkvec=checkvec-xdirvec.getPerpendicular();
                        n=n+1;
                        if(xmapptr.checkIfRoad(checkvec)
                            &&(xmapptr.checkIfDirectionSame(checkvec,xdirvec.getPerpendicular())||xmapptr.checkIfDirectionSame(checkvec,xdirvec.getPerpendicular()*(-1)))
                            &&(!xmapptr.checkIfFree(checkvec)))
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
                driver->setCrossDirection(xdirvec);
                Vec2d posvectmp(machine->getPositionX(),machine->getPositionY());
                xmapptr.setFree(posvectmp,true);
                driver->changeLane(machine,xdirvec); //inaczej
                posvectmp.setXY(machine->getPositionX(),machine->getPositionY());
                xmapptr.setFree(posvectmp,false);
                driver->resetObjective();


                //tutaj przejazd przez przecznice, ignorowanie mapy i jazda do przodu az mapa bedzie do przodu
            }
            else
            {
                driver->stop(machine);
            }

        }
        else
        {
            driver->brake(machine);
            //driver->slowdown(xmapptr,machine);
        }
    }

    return false;
}
