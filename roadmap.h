#ifndef ROADMAP_H
#define ROADMAP_H
#include <vector>
#include <memory>
#include "road.h"

class Roadmap
{
private:
    std::vector<std::unique_ptr<Road>> roads;
    std::vector<Vec2d> startpoints;
    int mapwidth,mapheight;
public:
    Roadmap();
    void maketestmap();
    bool getroadpos(int &xcnt, Vec2d &vecptr);
    void findstartpoints();
    bool choosestartpoint(Vec2d & xposvec);
    bool checkifinbound(Vec2d xposvec);
    bool checkifroad(Vec2d xposvec);
    bool checkifdirection(Vec2d xposvec, Vec2d xdirvec);
    bool checkiffree(Vec2d xposvec);
    bool checkiflanefree(Vec2d xposvec, float xrange, bool reverse=false);
    void setfree(Vec2d xposvec, bool isfree);
    Vec2d getdirection(Vec2d xposvec);
};

#endif // ROADMAP_H
