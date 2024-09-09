#include "vehicles.h"
#include "bike.h"
#include "car.h"
#include "truck.h"

Vehicles::Vehicles() {}

void Vehicles::addVehicle(int xcars, int xbikes, int xtrucks, Vec2d xvecpos)
{
    int vnumber[3];
    vnumber[0]=xcars;
    vnumber[1]=xbikes;
    vnumber[2]=xtrucks;
    for(auto& elem:vehicles)
    {
        elem->getMachinePtr()->countMachineType(vnumber);
    }
    Machine* machineptr;
    if((xcars>xbikes)&&(xcars>xtrucks))
    {
        machineptr=new Car(xvecpos);
    }
    else if(xbikes>xtrucks)
    {
        machineptr=new Bike(xvecpos);
    }
    else
    {
        machineptr=new Truck(xvecpos);
    }
    vehicles.push_back(std::make_unique<Vehicle>(Vehicle(machineptr)));
}

void Vehicles::deleteVehicle(int &xcnt)
{
    vehicles.erase(vehicles.begin()+xcnt);
    xcnt--;
}

bool Vehicles::checkIfVehiclesFull(int xnumber)
{
    if(static_cast<int>(vehicles.size())<xnumber)
    {
        return false;
    }
    return true;
}

bool Vehicles::getVehiclePtr(Vehicle *&vehicleptr,int xnum)
{
    if(xnum<static_cast<int>(vehicles.size()))
    {
        vehicleptr=vehicles[xnum].get();
        return true;
    }
    return false;
}
