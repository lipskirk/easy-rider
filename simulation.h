#ifndef SIMULATION_H
#define SIMULATION_H
#include <vector>
#include "vehicles.h"
#include "roadmap.h"

class Simulation
{
private:
    Roadmap roadmap;
    Vehicles vehicles;
public:
    Simulation();
    void updateSimulation(double xtime, int xcars, int xbikes, int xtrucks);
    void printVehiclesPosition(std::vector<Machine*> &xmachines);
    void printRoadsPosition(std::vector<Vec2d> &xroads);
};

#endif // SIMULATION_H
