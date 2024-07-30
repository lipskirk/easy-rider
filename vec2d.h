#ifndef VEC2D_H
#define VEC2D_H

class Vec2d
{
private:
    float x;
    float y;
public:
    Vec2d();
    Vec2d(float sx, float sy);
    float getx();
    float gety();
    void setxy(float sx, float sy);
    Vec2d perpendicular();

    Vec2d operator+(const Vec2d& other)
    {
        Vec2d tmpVec(x+other.x,y+other.y);
        return tmpVec;
    }

    Vec2d operator-(const Vec2d& other)
    {
        Vec2d tmpVec(x-other.x,y-other.y);
        return tmpVec;
    }

    Vec2d operator*(const float& other)
    {
        Vec2d tmpVec(x*other,y*other);
        return tmpVec;
    }

    bool operator==(const Vec2d& other)
    {
        if(x==other.x&&y==other.y)
        {
            return true;
        }
        return false;
    }
};

#endif // VEC2D_H
