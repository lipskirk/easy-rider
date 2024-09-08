#ifndef OBJECTIVEFORWARD_H
#define OBJECTIVEFORWARD_H
#include "objective.h"

class ObjectiveForward : public Objective
{
public:
    ObjectiveForward();
    bool move(Roadmap &xmapptr, Driver *&driver, Machine *&machine, Objective *&objective, float xdist) override;
    bool checkIfRoadStraight(Roadmap &xmapptr, Driver *&driver, Machine *&machine, Objective *&objective, float xdist);
};

#endif // OBJECTIVEFORWARD_H
