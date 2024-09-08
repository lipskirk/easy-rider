#ifndef ROADMAP_H
#define ROADMAP_H
#include <vector>
#include <memory>
#include "road.h"

class Roadmap
{
private:
    std::vector<std::unique_ptr<Road>> roads;
    std::vector<Vec2d> startPoints;
    int mapWidth;
    int mapHeight;


public:
    Roadmap();

    void makeTestMap();
    void findStartPoints();
    bool chooseStartPoint(Vec2d & xposvec);
    void setFree(Vec2d xposvec, bool isfree=true);

    bool checkIfInBounds(Vec2d xposvec);
    bool checkIfRoad(Vec2d xposvec);
    bool checkIfDirectionSame(Vec2d xposvec, Vec2d xdirvec);
    bool checkIfFree(Vec2d xposvec);
    bool checkIfLaneEmpty(Vec2d xposvec, float xrange, bool reverse=false);
    bool getRoadPosition(Vec2d &vecptr, int xnum);
    Vec2d getDirection(Vec2d xposvec);
};

#endif // ROADMAP_H
