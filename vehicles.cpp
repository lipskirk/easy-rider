#include "vehicles.h"
#include "bike.h"
#include "car.h"
#include "truck.h"

Vehicles::Vehicles() {}

bool Vehicles::getvehicle(int &xcnt, Vehicle *&vehicleptr)
{
    xcnt++;
    if(xcnt<static_cast<int>(vehicles.size()))
    {
        vehicleptr=vehicles[xcnt].get();
        return true;
    }
    return false;
}

void Vehicles::deletevehicle(int &xcnt)
{
    vehicles.erase(vehicles.begin()+xcnt);
    xcnt--;
}

bool Vehicles::checkifvehiclesfull(int xnumber)
{
    if(static_cast<int>(vehicles.size())<xnumber)
    {
        return false;
    }
    return true;
}

void Vehicles::addvehicle(int xc, int xb, int xt, Vec2d xvecpos)
{
    int vnumber[3];
    vnumber[0]=xc;
    vnumber[1]=xb;
    vnumber[2]=xt;
    for(auto& elem:vehicles)
    {
        elem->getmachine()->countup(vnumber);
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
