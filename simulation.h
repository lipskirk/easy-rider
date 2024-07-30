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
    void update(double xtime, int xcars, int xbikes, int xtrucks);
    void setvehicles(int v);
    void printvehiclespos(std::vector<Machine*> &xmachines);
    void printroadspos(std::vector<Vec2d> &xroads);
};

#endif // SIMULATION_H
