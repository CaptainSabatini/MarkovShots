#include "point3f.h"

Point3f::Point3f(const float x, const float y, const float z)
{
    myX = x;
    myY = y;
    myZ = z;
}

void Point3f::setX(const float x)
{    myX = x;}

void Point3f::setY(const float y)
{ myY = y;}

void Point3f::setZ(const float z)
{ myZ = z;}

float Point3f::getX()
{return myX;}

float Point3f::getY()
{return myY;}

float Point3f::getZ()
{return myZ;}
