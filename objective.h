#ifndef OBJECTIVE_H
#define OBJECTIVE_H
#include "roadmap.h"
#include "driver.h"
#include "machine.h"

class Objective
{
public:
    Objective();
    virtual bool scan(Roadmap &xmapptr, Driver *&driver, Machine *&machine, Objective *&objective)=0;
};

#endif // OBJECTIVE_H
