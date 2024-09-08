#include "simulation.h"
#include "vehicle.h"
#include <cstdlib>

Simulation::Simulation()
{
    srand(time(NULL));
    roadmap.makeTestMap();
    roadmap.findStartPoints();
}

void Simulation::updateSimulation(double xtime, int xcars, int xbikes, int xtrucks)
{
    if(!vehicles.checkIfVehiclesFull(xcars+xbikes+xtrucks)){
        Vec2d startpointvec;
        if(roadmap.chooseStartPoint(startpointvec))
        {
            vehicles.addVehicle(xcars,xbikes,xtrucks,startpointvec);
            roadmap.setFree(startpointvec,false);
        }
    }

    Vehicle* vehicletmp=nullptr;
    int cnt=0;

    while(vehicles.getVehiclePtr(vehicletmp,cnt))
    {
        if(!(vehicletmp->moveVehicle(roadmap,xtime)))
        {
            vehicles.deleteVehicle(cnt);
        }
        cnt++;
    }
}

void Simulation::printVehiclesPosition(std::vector<Machine*>& xmachines)
{
    Vehicle *vehicletmp=nullptr;
    int cnt=0;

    while(vehicles.getVehiclePtr(vehicletmp,cnt))
    {
        xmachines.push_back(vehicletmp->getMachinePtr());
        cnt++;
    }
}

void Simulation::printRoadsPosition(std::vector<Vec2d>& xroads)
{
    Vec2d vecptr;
    Vec2d vecdir0(0,0);
    int cnt=0;

    while(roadmap.getRoadPosition(vecptr,cnt))
    {
        if(roadmap.checkIfRoad(vecptr)){
            xroads.push_back(vecptr);
        }
        cnt++;
    }

}
