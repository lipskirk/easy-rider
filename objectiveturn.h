#ifndef OBJECTIVETURN_H
#define OBJECTIVETURN_H
#include "objective.h"

class ObjectiveTurn : public Objective
{
public:
    ObjectiveTurn();
    bool move(Roadmap &xmapptr, Driver *&driver, Machine *&machine, Objective *&objective, float xdist) override;
};

#endif // OBJECTIVETURN_H
