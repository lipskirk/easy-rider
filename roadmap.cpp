#include "roadmap.h"
#include <cstdlib>

Roadmap::Roadmap() {}

void Roadmap::makeTestMap()
{
    mapWidth=400;
    mapHeight=200;

    for(int j=0;j<mapHeight;j++)
    {
        for(int i=0;i<mapWidth;i++)
        {
            if((j>=60)&&(j<=63))
            {
                roads.push_back(std::make_unique<Road>(Road (true,i,j,-1,0)));
            }
            else if((j>=127)&&(j<130)&&(i<200))
            {
                roads.push_back(std::make_unique<Road>(Road (true,i,j,-1,0)));
            }
            else if((j>=160)&&(j<163))
            {
                roads.push_back(std::make_unique<Road>(Road (true,i,j,1,0)));
            }
            else if((j>63)&&(j<100)&&(i>=90)&&(i<93))
            {
                roads.push_back(std::make_unique<Road>(Road (true,i,j,0,1)));
            }
            else if((j>83)&&(j<127)&&(i>=43)&&(i<45))
            {
                roads.push_back(std::make_unique<Road>(Road (true,i,j,0,-1)));
            }
            else if((j<=83)&&(j>80)&&(i<45))
            {
                roads.push_back(std::make_unique<Road>(Road (true,i,j,-1,0)));
            }
            else if((j>=100)&&(j<102)&&(i>=205)&&(i<250))
            {
                roads.push_back(std::make_unique<Road>(Road (true,i,j,1,0)));
            }
            else if((j>=100)&&(j<160)&&(i>=248)&&(i<250))
            {
                roads.push_back(std::make_unique<Road>(Road (true,i,j,0,1)));
            }
            else if((i>=200)&&(i<205)&&(j<60))
            {
                roads.push_back(std::make_unique<Road>(Road (true,i,j,0,1)));
            }
            else if((i>=200)&&(i<205)&&(j>=63)&&(j<160))
            {
                roads.push_back(std::make_unique<Road>(Road (true,i,j,0,1)));
            }
            else if((i>=200)&&(i<205)&&(j>=163))
            {
                roads.push_back(std::make_unique<Road>(Road (true,i,j,0,-1)));
            }
            else
            {
                roads.push_back(std::make_unique<Road>(Road (true,i,j,0,0)));
            }
        }
    }
}



void Roadmap::findStartPoints()
{
    for(int j=0;j<mapHeight;j++)
    {
        for(int i=0;i<mapWidth;i++)
        {
            if((i==0)||(j==0)||(i==mapWidth-1)||(j==mapHeight-1))
            {
                Vec2d pos(roads[i+mapWidth*j]->getPositionX(),roads[i+mapWidth*j]->getPositionY());
                Vec2d pos2=pos-roads[i+mapWidth*j]->getDirection();
                if((pos2.getX()<0)||(pos2.getX()>=mapWidth)||(pos2.getY()<0)||(pos2.getY()>=mapHeight))
                {
                    startPoints.push_back(pos);
                }
            }
        }
    }
}

bool Roadmap::chooseStartPoint(Vec2d &xposvec)
{
    std::vector<Vec2d> occupiedpoints;
    Vec2d vpos=startPoints[rand()%(startPoints.size())];

    while(!checkIfFree(vpos))
    {
        bool newstartpoint=true;
        for(auto elem:occupiedpoints)
        {
            if(elem==vpos)
            {
                newstartpoint=false;
            }
        }
        if(newstartpoint==true)
        {
            occupiedpoints.push_back(vpos);
        }

        if(occupiedpoints.size()>=startPoints.size())
        {
            occupiedpoints.clear();
            return false;
        }
        vpos=startPoints[rand()%(startPoints.size())];
    }
    xposvec=vpos;
    occupiedpoints.clear();
    return true;
}

void Roadmap::setFree(Vec2d xposvec, bool isfree)
{
    roads[static_cast<int>(xposvec.getX())+mapWidth*static_cast<int>(xposvec.getY())]->setFree(isfree);
}




bool Roadmap::checkIfInBounds(Vec2d xposvec)
{
    if((xposvec.getX()<0)||(xposvec.getY()<0)||(xposvec.getX()>=mapWidth)||(xposvec.getY()>=mapHeight))
    {
        return false;
    }
    return true;
}

bool Roadmap::checkIfRoad(Vec2d xposvec)
{
    if(checkIfInBounds(xposvec))
    {
        return roads[static_cast<int>(xposvec.getX())+mapWidth*static_cast<int>(xposvec.getY())]->checkIfRoad();
    }
    return false;
}

bool Roadmap::checkIfDirectionSame(Vec2d xposvec, Vec2d xdirvec)
{
    if(checkIfInBounds(xposvec))
    {
        if(roads[static_cast<int>(xposvec.getX())+mapWidth*static_cast<int>(xposvec.getY())]->getDirection()==xdirvec)
        {
            return true;
        }
    }
    return false;
}

bool Roadmap::checkIfFree(Vec2d xposvec)
{
    if(checkIfInBounds(xposvec))
    {
        return roads[static_cast<int>(xposvec.getX())+mapWidth*static_cast<int>(xposvec.getY())]->checkIfFree();
    }
    return false;
}

bool Roadmap::checkIfLaneEmpty(Vec2d xposvec, float xrange, bool reverse)
{
    if(checkIfInBounds(xposvec))
    {
        Vec2d dirvec=roads[static_cast<int>(xposvec.getX())+mapWidth*static_cast<int>(xposvec.getY())]->getDirection();
        if(reverse)
        {
            dirvec=dirvec*(-1);
        }
        float freespace=0;
        while(freespace<xrange)
        {
            xposvec=xposvec+dirvec;
            if(!checkIfFree(xposvec))
            {
                return false;
            }
            freespace=freespace+1;
        }
        return true;
    }
    return false;
}

bool Roadmap::checkIfCrossLaneEmpty(Vec2d xposvec, float xrange, bool reverse)
{
    float n=0;
    Vec2d xdirvec=getDirection(xposvec).getPerpendicular();
    if(reverse)
    {
        xdirvec=xdirvec*(-1);
    }
    while(n<=xrange){
        xposvec=xposvec+xdirvec;
        n=n+1;
        if(checkIfRoad(xposvec)
            &&(checkIfDirectionSame(xposvec,xdirvec.getPerpendicular())||checkIfDirectionSame(xposvec,xdirvec.getPerpendicular()*(-1)))
            &&(!checkIfFree(xposvec)))
        {
            return false;
        }
    }
    return true;
}

bool Roadmap::getRoadPosition(Vec2d &vecptr, int xnum)
{
    if(xnum<static_cast<int>(roads.size()))
    {
        vecptr.setXY(roads[xnum]->getPositionX(),roads[xnum]->getPositionY());
        return true;
    }
    return false;
}

Vec2d Roadmap::getDirection(Vec2d xposvec)
{
    return roads[static_cast<int>(xposvec.getX())+mapWidth*static_cast<int>(xposvec.getY())]->getDirection();
}
