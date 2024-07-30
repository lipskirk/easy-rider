#include "vec2d.h"

Vec2d::Vec2d() {}

Vec2d::Vec2d(float sx, float sy)
{
    x=sx;
    y=sy;
}

float Vec2d::getx()
{
    return x;
}

float Vec2d::gety()
{
    return y;
}

void Vec2d::setxy(float sx, float sy)
{
    x=sx;
    y=sy;
}

Vec2d Vec2d::perpendicular()
{
    Vec2d v;
    v.x = y;
    v.y = x*(-1);
    return v;
}
