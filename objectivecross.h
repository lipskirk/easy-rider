#ifndef OBJECTIVECROSS_H
#define OBJECTIVECROSS_H
#include "objective.h"

class ObjectiveCross : public Objective
{
public:
    ObjectiveCross();
    bool scan(Roadmap &xmapptr, Driver *&driver, Machine *&machine, Objective *&objective) override;
};

#endif // OBJECTIVECROSS_H
