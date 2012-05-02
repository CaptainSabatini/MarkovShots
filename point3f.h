#ifndef POINT3F_H
#define POINT3F_H

class Point3f
{
private:
    float myX;
    float myY;
    float myZ;
public:
    Point3f(const float x = 0, const float y = 0, const float z = 0);
    void setX(const float x);
    void setY(const float y);
    void setZ(const float z);
    float getX();
    float getY();
    float getZ();
};

#endif // POINT3F_H
