#ifndef VEHICLES_H
#define VEHICLES_H
#include <vector>
#include <memory>
#include "vehicle.h"

class Vehicles
{
private:
    std::vector<std::unique_ptr<Vehicle>> vehicles;

public:
    Vehicles();
    void addVehicle(int xc, int xb, int xt, Vec2d xvecpos);//zamienic osobne liczby na tablice
    void deleteVehicle(int &xcnt);
    bool checkIfVehiclesFull(int xnumber);
    bool getVehiclePtr(Vehicle *&vehicleptr, int xnum);
};

#endif // VEHICLES_H
