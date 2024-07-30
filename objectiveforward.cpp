#include "objectiveforward.h"
#include "objectivecross.h"
#include "objectivejoin.h"
#include "objectivestop.h"
#include "objectiveturn.h"

ObjectiveForward::ObjectiveForward() {}

bool ObjectiveForward::scan(Roadmap &xmapptr, Driver *&driver, Machine *&machine, Objective *&objective)
{
    bool objectivechanged=lookforturns(xmapptr,driver,machine,objective);//szukanie zakretow

    float range=(machine->getspeed())/2;
    Vec2d vecpos(machine->getposx(),machine->getposy());
    Vec2d xdirvec=xmapptr.getdirection(vecpos);

    if(driver->checkifovertaking())
    {//wyprzedzał, sprawdzenie czy skończył
        Vec2d rightPosVec=vecpos-xdirvec.perpendicular();//pole po prawej do sprawdzenia
        int distfree=0;
        while(distfree<(driver->getdisttoovertake()))
        {//sprawdzenie kolejnych pól po prawej
            if(xmapptr.checkifroad(rightPosVec)
                &&xmapptr.checkifdirection(rightPosVec,xdirvec))
            {//jest prosto
                if(!xmapptr.checkiffree(rightPosVec))
                {//jest zajęte, dalej wyprzedza
                    driver->overtakingdone();
                    break;
                }
            }
            //następne pole
            distfree=distfree+1;
            rightPosVec=rightPosVec+xdirvec;
        }
    }
    if(!driver->checkifovertaking())
    {//nie wyprzedzał lub skończył, trzeba zjechac do prawej
        Vec2d rightPosVec=vecpos-xdirvec.perpendicular();
        if(xmapptr.checkifroad(rightPosVec)
            &&xmapptr.checkifdirection(rightPosVec,xdirvec))
        {
            if(xmapptr.checkiffree(rightPosVec)
                &&xmapptr.checkiflanefree(rightPosVec,range)
                &&xmapptr.checkiflanefree(rightPosVec,range,true))
            {//wolne po prawej, można zmienić pas

                //to jako zmiana pasa przed drivera?------
                Vec2d posvectmp(machine->getposx(),machine->getposy());
                xmapptr.setfree(posvectmp,true);
                //roads[static_cast<int>(elem->getposy())*mapwidth+static_cast<int>(elem->getposx())]->makefree();
                driver->changelane(machine,xdirvec.perpendicular()*(-1));
                posvectmp.setxy(machine->getposx(),machine->getposy());
                xmapptr.setfree(posvectmp,true);
                //roads[static_cast<int>(elem->getposy())*mapwidth+static_cast<int>(elem->getposx())]->makeoccupied();
                //--------------------
            }
        }
    }

    //szukanie przeszkod na pasie ruchu wprzod
    float disttoobst=0;
    bool obstacle=false;
    Vec2d forwardPosVec=vecpos;//pole na wprost do sprawdzenia
    while(disttoobst<(range))
    {//sprawdzanie kolejnych pól w przód
        disttoobst=disttoobst+1;
        forwardPosVec=forwardPosVec+xdirvec;
        if(xmapptr.checkifroad(forwardPosVec)
            &&xmapptr.checkifdirection(forwardPosVec,xdirvec)
            &&!xmapptr.checkiffree(forwardPosVec))
        {//nie jest wolna
            obstacle=true;
            break;
        }
    }
    if(obstacle)
    {//jest przeszkoda na wprost
        if(disttoobst<driver->getdisttoobstacle())
        {//przeszkoda blizej niz poprzednio
            //sprawdzenie czy może zmienić pas na lewy
            Vec2d lPosVec=vecpos+xdirvec.perpendicular();//pole po lewej do sprawdzenia

            if(xmapptr.checkifroad(lPosVec)
                &&xmapptr.checkifdirection(lPosVec,xdirvec))
            {
                if(xmapptr.checkiffree(lPosVec)
                    &&xmapptr.checkiflanefree(lPosVec,range)
                    &&xmapptr.checkiflanefree(lPosVec,range,true))
                {//ZMIANA PASA NA LEWY, rozpoczecie wyprzedzania

                    //to jako zmiana pasa przed drivera?------
                    Vec2d posvectmp(machine->getposx(),machine->getposy());
                    xmapptr.setfree(posvectmp,true);
                    //roads[static_cast<int>(elem->getposy())*mapwidth+static_cast<int>(elem->getposx())]->makefree();
                    driver->changelane(machine,xdirvec.perpendicular());
                    driver->startovertaking();
                    driver->setdisttoovertake(disttoobst);
                    posvectmp.setxy(machine->getposx(),machine->getposy());
                    xmapptr.setfree(posvectmp,true);
                    //roads[static_cast<int>(elem->getposy())*mapwidth+static_cast<int>(elem->getposx())]->makeoccupied();
                    //-----------------------
                }
                else
                {//zajęte
                    //ZWOLNIJ
                    driver->brake(machine);

                }
            }
            else
            {//zajęte
                //ZWOLNIJ
                driver->brake(machine);
            }
        }
    }
    else
    {//brak przeszkód, przyspieszanie i jazda prosto
        driver->accelerate(machine);
    }
    driver->setdisttoobstacle(disttoobst);
    return objectivechanged;
}

bool ObjectiveForward::lookforturns(Roadmap &xmapptr, Driver *&driver, Machine *&machine, Objective *&objective)
{
    bool objectivechanged=false;
    float xrange=(machine->getspeed())/2;
    Vec2d xposvec(machine->getposx(),machine->getposy());
    bool right=driver->checkifturnright();
    Vec2d xdirvec=xmapptr.getdirection(xposvec);
    Vec2d xturndirvec=xdirvec.perpendicular();
    if(right)
    {
        xturndirvec=xturndirvec*(-1);
    }

    float disttoturn=0;//dystans do zakretu
    xposvec=xposvec+xturndirvec;//pole z boku

    do
    {//sprawdzenie kolejnego pola
        if(xmapptr.checkifroad(xposvec))
        {//jest drogą
            if(xmapptr.checkifdirection(xposvec,xdirvec))
            {//jest prosto
                xposvec=xposvec+xturndirvec;//do spr. następne pole w kierunku skrętu
            }
            else if(xmapptr.checkifdirection(xposvec,xdirvec*(-1)))
            {//jest w tył
                break;
            }
            else
            {// jest w bok
                xposvec=xposvec+xdirvec;
                disttoturn=disttoturn+1;//do spr. następne pole prosto
            }
        }
        else
        {//nie jest drogą
            break;
        }
    }
    while(disttoturn<xrange);

    do
    {//sprawdzenie kolejnego pola
        if(xmapptr.checkifroad(xposvec))
        {//jest drogą
            if(xmapptr.checkifdirection(xposvec,xdirvec))
            {//jest prosto
                xposvec=xposvec+xturndirvec;//do spr. następne pole w kierunku skrętu
            }
            else if(xmapptr.checkifdirection(xposvec,xdirvec*(-1)))
            {//jest w tył
                xposvec=xposvec+xdirvec;
                disttoturn=disttoturn+1;//do spr. następne pole prosto
            }
            else
            {// jest w bok
                break;
            }
        }
        else
        {//nie jest drogą
            xposvec=xposvec+xdirvec;
            disttoturn=disttoturn+1;//do spr. następne pole prosto
        }
    }
    while(disttoturn<xrange);

    Vec2d xposvec2=xposvec-xturndirvec;
    while(!xmapptr.checkifroad(xposvec2))
    {//na wprost nie ma drogi
        xposvec2=xposvec2-xdirvec;//cofnięcie do punktu, gdzie droga się skończyła
        disttoturn=disttoturn-1;
    }
    xposvec=xposvec2+xturndirvec;

    bool fw=false;
    Vec2d xposvec3=xposvec;
    do
    {
        xposvec3=xposvec3+xdirvec;
    }
    while(xmapptr.checkifroad(xposvec3));

    xposvec3=xposvec3-xturndirvec;
    if(xmapptr.checkifdirection(xposvec3,xdirvec))
    {
        fw=true;
    }
    if(xmapptr.checkifdirection(xposvec2,xdirvec))
    {//nie ma przecznicy na drodze
        if(xmapptr.checkifdirection(xposvec,xturndirvec))
        {
            if(driver->chooseifturn(disttoturn,right,!fw))
            {
                objective=new ObjectiveTurn;
                objectivechanged=true;
            }
        }
        else if(!fw)
        {
            Vec2d xposvec4=xposvec2;
            while(xmapptr.checkifdirection(xposvec4,xdirvec))
            {
                xposvec4=xposvec4-xturndirvec;
            }
            if(xmapptr.checkifdirection(xposvec4,xturndirvec*(-1)))
            {
                if(driver->chooseifturn(disttoturn,!right,!fw))
                {
                    objective=new ObjectiveTurn;
                    objectivechanged=true;
                }
            }
            else if(xmapptr.checkifinbound(xposvec3))
            {
                driver->setistostop(disttoturn);
                objective=new ObjectiveStop;
                objectivechanged=true;
            }
        }
    }
    else
    {//jest przecznica na drodze
        if(!xmapptr.checkifdirection(xposvec2,xturndirvec))
        {
            right=!right;
        }
        if(driver->chooseifjoin(disttoturn,right,!fw))
        {
            objective=new ObjectiveJoin;
        }
        else
        {
            objective=new ObjectiveCross;
        }
        objectivechanged=true;
    }
    return objectivechanged;
}
