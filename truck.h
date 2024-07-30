#ifndef TRUCK_H
#define TRUCK_H
#include"machine.h"

class Truck :public Machine
{
public:
    Truck(Vec2d xposvec);
    void countup(int vnumber[]) override;
    char gettype() override;
};

#endif // TRUCK_H
