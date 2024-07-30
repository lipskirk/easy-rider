#ifndef OBJECTIVEJOIN_H
#define OBJECTIVEJOIN_H
#include "objective.h"

class ObjectiveJoin : public Objective
{
public:
    ObjectiveJoin();
    bool scan(Roadmap &xmapptr, Driver *&driver, Machine *&machine, Objective *&objective) override;
};

#endif // OBJECTIVEJOIN_H
