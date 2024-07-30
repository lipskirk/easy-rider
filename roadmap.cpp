#include "roadmap.h"
#include <cstdlib>

Roadmap::Roadmap() {}

void Roadmap::maketestmap()
{
    mapwidth=400;
    mapheight=200;

    for(int j=0;j<mapheight;j++)
    {
        for(int i=0;i<mapwidth;i++)
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
                roads.push_back(std::make_unique<Road>(Road (true,i,j,0,1)));
            }

            else
            {
                roads.push_back(std::make_unique<Road>(Road (true,i,j,0,0)));
            }
        }
    }
}

bool Roadmap::getroadpos(int &xcnt, Vec2d &vecptr)
{
    xcnt++;
    if(xcnt<static_cast<int>(roads.size()))
    {
        vecptr.setxy(roads[xcnt]->getposx(),roads[xcnt]->getposy());
        return true;
    }
    return false;
}

void Roadmap::findstartpoints()
{
    for(int j=0;j<mapheight;j++)
    {
        for(int i=0;i<mapwidth;i++)
        {
            if((i==0)||(j==0)||(i==mapwidth-1)||(j==mapheight-1))
            {
                Vec2d pos(roads[i+mapwidth*j]->getposx(),roads[i+mapwidth*j]->getposy());
                Vec2d pos2=pos-roads[i+mapwidth*j]->getdirection();
                if((pos2.getx()<0)||(pos2.getx()>=mapwidth)||(pos2.gety()<0)||(pos2.gety()>=mapheight))
                {
                    startpoints.push_back(pos);
                }
            }
        }
    }
}

bool Roadmap::choosestartpoint(Vec2d &xposvec)
{
    std::vector<Vec2d> occupiedpoints;
    Vec2d vpos=startpoints[rand()%(startpoints.size())];

    while(!checkiffree(vpos))
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

        if(occupiedpoints.size()>=startpoints.size())
        {
            occupiedpoints.clear();
            return false;
        }
        vpos=startpoints[rand()%(startpoints.size())];
    }
    xposvec=vpos;
    occupiedpoints.clear();
    return true;
}

void Roadmap::setfree(Vec2d xposvec, bool isfree)
{
    roads[static_cast<int>(xposvec.getx())+mapwidth*static_cast<int>(xposvec.gety())]->setfree(isfree);
}

Vec2d Roadmap::getdirection(Vec2d xposvec)
{
    return roads[static_cast<int>(xposvec.getx())+mapwidth*static_cast<int>(xposvec.gety())]->getdirection();
}

bool Roadmap::checkifinbound(Vec2d xposvec)
{
    if((xposvec.getx()<0)||(xposvec.gety()<0)||(xposvec.getx()>=mapwidth)||(xposvec.gety()>=mapheight))
    {
        return false;
    }
    return true;
}

bool Roadmap::checkifroad(Vec2d xposvec)
{
    if(checkifinbound(xposvec))
    {
        return roads[static_cast<int>(xposvec.getx())+mapwidth*static_cast<int>(xposvec.gety())]->checkifroad();
    }
    return false;
}

bool Roadmap::checkifdirection(Vec2d xposvec, Vec2d xdirvec)
{
    if(checkifinbound(xposvec))
    {
        if(roads[static_cast<int>(xposvec.getx())+mapwidth*static_cast<int>(xposvec.gety())]->getdirection()==xdirvec)
        {
            return true;
        }
    }
    return false;
}

bool Roadmap::checkiffree(Vec2d xposvec)
{
    if(checkifinbound(xposvec))
    {
        return roads[static_cast<int>(xposvec.getx())+mapwidth*static_cast<int>(xposvec.gety())]->checkiffree();
    }
    return false;
}

bool Roadmap::checkiflanefree(Vec2d xposvec, float xrange, bool reverse)
{
    if(checkifinbound(xposvec))
    {
        Vec2d dirvec=roads[static_cast<int>(xposvec.getx())+mapwidth*static_cast<int>(xposvec.gety())]->getdirection();
        if(reverse)
        {
            dirvec=dirvec*(-1);
        }
        float freespace=0;
        while(freespace<xrange)
        {
            xposvec=xposvec+dirvec;
            if(!checkiffree(xposvec))
            {
                return false;
            }
            freespace=freespace+1;
        }
        return true;
    }
    return false;
}
