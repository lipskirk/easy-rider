#ifndef OBJECTIVETURN_H
#define OBJECTIVETURN_H
#include "objective.h"

class ObjectiveTurn : public Objective
{
public:
    ObjectiveTurn();
    bool scan(Roadmap &xmapptr, Driver *&driver, Machine *&machine, Objective *&objective) override;
};

#endif // OBJECTIVETURN_H
