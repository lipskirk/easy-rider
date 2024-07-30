#ifndef VEHICLE_H
#define VEHICLE_H
#include "objective.h"
#include "machine.h"
#include "driver.h"
#include "roadmap.h"

class Vehicle
{
private:
    Driver* driver;
    Machine* machine;
    Objective* obj;
public:
    Vehicle(Machine *xmachineptr);
    void lookaround(Roadmap &xmapptr);
    bool move(Roadmap &xmapptr, float xtime);
    //template <typename T> void setobjective(){obj=new T;}
    Machine* getmachine();
    Objective* getobjective();
};

#endif // VEHICLE_H

