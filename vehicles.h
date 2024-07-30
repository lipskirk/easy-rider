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
    void deletevehicle(int &xcnt);
    bool checkifvehiclesfull(int xnumber);
    void addvehicle(int xc, int xb, int xt, Vec2d xvecpos);
    bool getvehicle(int &n, Vehicle *&vehicleptr);
};

#endif // VEHICLES_H
