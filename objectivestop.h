#ifndef OBJECTIVESTOP_H
#define OBJECTIVESTOP_H
#include "objective.h"

class ObjectiveStop : public Objective
{
public:
    ObjectiveStop();
    bool scan(Roadmap &xmapptr, Driver *&driver, Machine *&machine, Objective *&objective) override;
};

#endif // OBJECTIVESTOP_H
