#ifndef OBJECTIVEJOIN_H
#define OBJECTIVEJOIN_H
#include "objective.h"

class ObjectiveJoin : public Objective
{
public:
    ObjectiveJoin();
    bool move(Roadmap &xmapptr, Driver *&driver, Machine *&machine, Objective *&objective, float xdist) override;
};

#endif // OBJECTIVEJOIN_H
