#ifndef OBJECTIVESTOP_H
#define OBJECTIVESTOP_H
#include "objective.h"

class ObjectiveStop : public Objective
{
public:
    ObjectiveStop();
    bool move(Roadmap &xmapptr, Driver *&driver, Machine *&machine, Objective *&objective, float xdist) override;
};

#endif // OBJECTIVESTOP_H
