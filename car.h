#ifndef CAR_H
#define CAR_H
#include "machine.h"

class Car :public Machine
{
public:
    Car(Vec2d xposvec);
    void countup(int vnumber[]) override;
    char gettype() override;
};

#endif // CAR_H
