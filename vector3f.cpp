#include "vector3f.h"

#include <math.h>

Vector3f::Vector3f(const float x, const float y, const float z)
{
        myX = x;
        myY = y;
        myZ = z;
}

Vector3f::Vector3f(const Vector3f& source)
{
        myX = source.getX();
        myY = source.getY();
        myZ = source.getZ();
}

void Vector3f::set(const float x, const float y, const float  z)
{
        myX = x;
        myY = y;
        myZ = z;
}

float Vector3f::getX() const
{return myX;}

float Vector3f::getY() const
{return myY;}

float Vector3f::getZ() const
{return myZ;}

float Vector3f::length() const
{return sqrt((float)(myX*myX)+(myY*myY) +(myZ*myZ));}

void Vector3f::add(const Vector3f& source)
{
        myX += source.getX();
        myY += source.getY();
        myZ += source.getZ();
}

void Vector3f::sub(const Vector3f& source)
{
        myX -= source.getX();
        myY -= source.getY();
        myZ -= source.getZ();
}

void Vector3f::normalize()
{
        float mag = length();
        myX = myX/mag;
        myY = myY/mag;
        myZ = myZ/mag;
}

float Vector3f::dot(const Vector3f& source)
{return((myX*source.getX()) + myY*source.getY() + myZ*source.getZ());}

Vector3f Vector3f::cross(const Vector3f& source)
{
    Vector3f crossProduct = Vector3f();
    crossProduct.set(myY*source.getZ() - myZ*source.getY(),
                     myZ*source.getX() - myX*source.getZ(),
                     myX*source.getY() - myY*source.getX());
    return crossProduct;
}
