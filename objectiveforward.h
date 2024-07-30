#ifndef OBJECTIVEFORWARD_H
#define OBJECTIVEFORWARD_H
#include "objective.h"

class ObjectiveForward : public Objective
{
public:
    ObjectiveForward();
    bool scan(Roadmap &xmapptr, Driver *&driver, Machine *&machine, Objective *&objective) override;
    bool lookforturns(Roadmap &xmapptr, Driver *&driver, Machine *&machine, Objective *&objective);
};

#endif // OBJECTIVEFORWARD_H
