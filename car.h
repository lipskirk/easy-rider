#ifndef CAR_H
#define CAR_H
#include "machine.h"

class Car :public Machine
{
public:
    Car(Vec2d xposvec);
    void countMachineType(int vnumber[]) override;
    char getMachineType() override;
};

#endif // CAR_H
