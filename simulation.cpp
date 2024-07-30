#include "simulation.h"
#include "vehicle.h"
#include <cstdlib>

Simulation::Simulation()
{
    srand(time(NULL));
    roadmap.maketestmap();
    roadmap.findstartpoints();
}

void Simulation::update(double xtime, int xcars, int xbikes, int xtrucks)
{
    if(!vehicles.checkifvehiclesfull(xcars+xbikes+xtrucks)){
        Vec2d startpointvec;
        if(roadmap.choosestartpoint(startpointvec))
        {
            vehicles.addvehicle(xcars,xbikes,xtrucks,startpointvec);
            roadmap.setfree(startpointvec,false);
        }
    }

    Vehicle* vehicletmp=nullptr;
    int cnt=-1;

    while(vehicles.getvehicle(cnt,vehicletmp))
    {
        vehicletmp->lookaround(roadmap);
        if(!(vehicletmp->move(roadmap,xtime)))
        {
            vehicles.deletevehicle(cnt);
        }
    }
}

void Simulation::printvehiclespos(std::vector<Machine*>& xmachines)
{
    Vehicle *vehicletmp=nullptr;
    int cnt=-1;

    while(vehicles.getvehicle(cnt,vehicletmp))
    {
        xmachines.push_back(vehicletmp->getmachine());
    }
}

void Simulation::printroadspos(std::vector<Vec2d>& xroads)
{
    Vec2d vecptr;
    Vec2d vecdir0(0,0);
    int cnt=-1;

    while(roadmap.getroadpos(cnt,vecptr))
    {
        if(roadmap.checkifroad(vecptr)){
            xroads.push_back(vecptr);
        }
    }

}
