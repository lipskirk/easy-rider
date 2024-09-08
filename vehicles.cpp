#include "vehicles.h"
#include "bike.h"
#include "car.h"
#include "truck.h"

Vehicles::Vehicles() {}

bool Vehicles::getVehiclePtr(Vehicle *&vehicleptr,int xnum)
{
    if(xnum<static_cast<int>(vehicles.size()))
    {
        vehicleptr=vehicles[xnum].get();
        return true;
    }
    return false;
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

void Vehicles::addVehicle(int xc, int xb, int xt, Vec2d xvecpos)
{
    int vnumber[3];
    vnumber[0]=xc;
    vnumber[1]=xb;
    vnumber[2]=xt;
    for(auto& elem:vehicles)
    {
        elem->getMachinePtr()->countMachineType(vnumber);
    }
    Machine* machineptr;
    if((xc>xb)&&(xc>xt))
    {
        machineptr=new Car(xvecpos);
    }
    else if(xb>xt)
    {
        machineptr=new Bike(xvecpos);
    }
    else
    {
        machineptr=new Truck(xvecpos);
    }
    vehicles.push_back(std::make_unique<Vehicle>(Vehicle(machineptr)));
}
