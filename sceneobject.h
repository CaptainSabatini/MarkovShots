#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "rigidbody.h"

class SceneObject : public RigidBody
{
private:
    enum {BOXSIZE = 8};
    Vector3f myBBox[BOXSIZE];
    void setBoundBox(const Vector3f bounds[8]);
    void drawCube();
    void drawCylinder();
    void drawFloor();
    void drawGridLine(float length);
    float getLargeX();
    float getSmallX();
    float getLargeY();
    float getSmallY();
    float getLargeZ();
    float getSmallZ();

public:
    //Constructors
    SceneObject(float x=0.0f, float y=0.0f, float z=0.0f);
    //SceneObject(SceneObject& source);
    ///////////////////////////////////////////
    //getBox
    //Returns the array of bounding points as a pointer
    //Input: void
    //Output: pointer to a Point
    ///////////////////////////////////////////
    Vector3f* getBoundBox();

    ///////////////////////////////////////////
    //getBoundAt
    //Returns one of the points as requested
    //Input: int bound, which element to return
    //Output: the Point at desired element
    ///////////////////////////////////////////
    Vector3f getBoundAt(int bound);

    void drawObject(const int shapeType);

    float getWidth();
    float getHeight();
    float getDepth();

    void getGlobBox(Vector3f setup[]);
};

#endif // SCENEOBJECT_H
