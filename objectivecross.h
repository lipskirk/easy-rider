#ifndef OBJECTIVECROSS_H
#define OBJECTIVECROSS_H
#include "objective.h"

class ObjectiveCross : public Objective
{
public:
    ObjectiveCross();
    bool move(Roadmap &xmapptr, Driver *&driver, Machine *&machine, Objective *&objective, float xdist) override;
};

#endif // OBJECTIVECROSS_H
