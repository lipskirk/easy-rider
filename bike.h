#ifndef BIKE_H
#define BIKE_H
#include "machine.h"

class Bike :public Machine
{
public:
    Bike(Vec2d xposvec);
    void countup(int vnumber[]) override;
    char gettype() override;
};

#endif // BIKE_H
