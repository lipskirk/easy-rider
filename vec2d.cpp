#include "vec2d.h"

Vec2d::Vec2d() {}

Vec2d::Vec2d(float sx, float sy)
{
    x=sx;
    y=sy;
}

float Vec2d::getX()
{
    return x;
}

float Vec2d::getY()
{
    return y;
}

void Vec2d::setXY(float sx, float sy)
{
    x=sx;
    y=sy;
}

Vec2d Vec2d::getPerpendicular()
{
    Vec2d v;
    v.x = y;
    v.y = x*(-1);
    return v;
}
