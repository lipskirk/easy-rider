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
    bool moveVehicle(Roadmap &xmapptr, float xtime);
    Machine* getMachinePtr();
};

#endif // VEHICLE_H

