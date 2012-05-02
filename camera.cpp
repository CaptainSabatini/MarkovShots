#include "camera.h"
#include <math.h>
#include <GL/gl.h>

//Constructors
Camera::Camera()
{
    FOV = 15;
    aspectRatio = 2;
    distance = 0.1;
    maxN = 100;
    setAim3f(0, 0, 1);
    setUp3f(0, 1, 0);
    setRight3f(1, 0, 0);
    setPos3f(0, 0 , -1);
}

Camera::Camera(Camera& source)
{
    FOV = source.getFOV();
    aspectRatio = source.getAspectRatio();
    distance = source.getDistance();
    maxN = source.getMaxN();
    myUp = source.getUp();
    myRight = source.getRight();
    myAim = source.getAim();
    myPos = source.getPos();
}

//Getters
float Camera::getFOV()
{return FOV;}

float Camera::getAspectRatio()
{return aspectRatio;}

float Camera::getDistance()
{return distance;}

float Camera::getMaxN()
{return maxN;}

//Setters
void Camera::setFOV(float fov)
{FOV = fov;}

void Camera::setAspectRatio(float ratio)
{aspectRatio = ratio;}

void Camera::setDistance(float d)
{distance = d;}

void Camera::setmaxN(float n)
{maxN = n;}

/////////////////////////////////////////////////////////////////////
//Returns wether the point is in view
//This is solely determined by the point being between d and maxN
//FOV is not taken into account because zoom could be larger than screen
//
//Input: Point to compare
//Output: bool saying in or out of view
/////////////////////////////////////////////////////////////////////
bool Camera::isInView(Vector3f p)
{
    Vector3f transP = Vector3f();
    Matrix3f toCamera = Matrix3f();
    toCamera = getGlobaltoLocal();
    toCamera.transformPoint(transP, p);
    return ((p.getZ() <= maxN) && (p.getZ() >= distance));
}

/////////////////////////////////////////////////////////////////////
//This method projects a 3D point on the global coordinates into
//a 2D point in the camera's image plane (can be out of field of view)
//
//Input: Point p to project to a Point Q(by reference)
//Output: bool verifying projection
/////////////////////////////////////////////////////////////////////
/*bool Camera::project(const Point3f p, Point3f& Q)
{

}*/

void Camera::moveEye(int dir)
{
    Vector3f aim = myAim;
    myAim.normalize();
    myUp.normalize();
    myRight.normalize();
    switch(dir)
    {
        //UP
        case 0: myPos.set(myPos.getX()+myUp.getX(),
                          myPos.getY()+myUp.getY(),
                          myPos.getZ()+myUp.getZ());
            break;
        //Down
        case 1: myPos.set(myPos.getX()-myUp.getX(),
                          myPos.getY()-myUp.getY(),
                          myPos.getZ()-myUp.getZ());
            break;
        //Left
        case 2: myPos.set(myPos.getX()-myRight.getX(),
                          myPos.getY()-myRight.getY(),
                          myPos.getZ()-myRight.getZ());
            break;
        //Right
        case 3: myPos.set(myPos.getX()+myRight.getX(),
                          myPos.getY()+myRight.getY(),
                          myPos.getZ()+myRight.getZ());
            break;
        //Forward
        case 4: myPos.set(myPos.getX()+myAim.getX(),
                          myPos.getY()+myAim.getY(),
                          myPos.getZ()+myAim.getZ());
            break;
        //Backward
        case 5: myPos.set(myPos.getX()-myAim.getX(),
                          myPos.getY()-myAim.getY(),
                          myPos.getZ()-myAim.getZ());
            break;
    }
    myAim = aim;
}

void Camera::moveLook(int dir)
{
    myAim.normalize();
    myUp.normalize();
    myRight.normalize();
    bool rotUp = false;
    switch(dir)
    {
        //UP
        case 0: myAim.set(myAim.getX()+myUp.getX(),
                          myAim.getY()+myUp.getY(),
                          myAim.getZ()+myUp.getZ());
                rotUp = true;
            break;
        //Down
        case 1: myAim.set(myAim.getX()-myUp.getX(),
                          myAim.getY()-myUp.getY(),
                          myAim.getZ()-myUp.getZ());
                rotUp = true;
            break;
        //Left
        case 2: myAim.set(myAim.getX()-myRight.getX(),
                          myAim.getY()-myRight.getY(),
                          myAim.getZ()-myRight.getZ());
            break;
        //Right
        case 3: myAim.set(myAim.getX()+myRight.getX(),
                          myAim.getY()+myRight.getY(),
                          myAim.getZ()+myRight.getZ());
    }
    myAim.normalize();
    if(rotUp)
        myUp = myRight.cross(myAim);
    else
        myRight = myAim.cross(myUp);
    /*Vector3f aim = myAim;
    myAim.normalize();
    Vector3f up = Vector3f(0, 1, 0);
    myRight = myAim.cross(up);
    myRight.normalize();
    myUp = myRight.cross(myAim);
    myUp.normalize();
    myAim = aim;*/

    /*if(dir == 3)
    {
        Vector3f aim = myAim;
        Vector3f right = myRight;
        float rads = 5.0/57.2957795;
        myAim.set((cos(1.5708f + rads)*aim.getX()) + (cos(rads) * right.getX()),
                  (cos(1.5708f + rads)*aim.getY()) + (cos(rads) * right.getY()),
                  (cos(1.5708f + rads)*aim.getZ()) + (cos(rads) * right.getZ()));
        myRight.set((cos(rads) * aim.getX()) + (cos(1.5708f - rads) * right.getX()),
                    (cos(rads) * aim.getY()) + (cos(1.5708f - rads) * right.getY()),
                    (cos(rads) * aim.getZ()) + (cos(1.5708f - rads) * right.getZ()));
        myAim.normalize();
        myRight.normalize();
    }
    else if(dir == 2)
    {
        Vector3f aim = myAim;
        Vector3f right = myRight;
        float rads = -5.0/57.2957795;
        myAim.set((cos(1.5708f + rads)*aim.getX()) + (cos(rads) * right.getX()),
                  (cos(1.5708f + rads)*aim.getY()) + (cos(rads) * right.getY()),
                  (cos(1.5708f + rads)*aim.getZ()) + (cos(rads) * right.getZ()));
        myRight.set((cos(rads) * myAim.getX()) + (cos(1.5708f - rads) * right.getX()),
                    (cos(rads) * myAim.getY()) + (cos(1.5708f - rads) * right.getY()),
                    (cos(rads) * myAim.getZ()) + (cos(1.5708f - rads) * right.getZ()));
        myAim.normalize();
        myRight.normalize();
    }*/

}

void Camera::rotateLoc(float deg, float x, float y, float z) {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        float Transform[16];
        Transform[0] = 1.0f;
                Transform[5] = 1.0f;
                Transform[10] = 1.0f;
                Transform[15] = 1.0f;
                Transform[12] = myPos.getX();
                Transform[13] = myPos.getY();
                Transform[14] = myPos.getZ();
        glLoadMatrixf(Transform);
        glRotatef(deg, x,y,z);
        glGetFloatv(GL_MODELVIEW_MATRIX, Transform);
        glPopMatrix();
}

void Camera::setView() {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        float Transform[16];
        Transform[0] = 1.0f;
                Transform[5] = 1.0f;
                Transform[10] = 1.0f;
                Transform[15] = 1.0f;
                Transform[12] = myPos.getX();
                Transform[13] = myPos.getY();
                Transform[14] = myPos.getZ();
        float viewmatrix[16]={//Remove the three - for non-inverted z-axis
                                                  Transform[0], Transform[4], -Transform[8], 0,
                                                  Transform[1], Transform[5], -Transform[9], 0,
                                                  Transform[2], Transform[6], -Transform[10], 0,

                                                  -(Transform[0]*Transform[12] +
                                                  Transform[1]*Transform[13] +
                                                  Transform[2]*Transform[14]),

                                                  -(Transform[4]*Transform[12] +
                                                  Transform[5]*Transform[13] +
                                                  Transform[6]*Transform[14]),

                                                  //add a - like above for non-inverted z-axis
                                                  (Transform[8]*Transform[12] +
                                                  Transform[9]*Transform[13] +
                                                  Transform[10]*Transform[14]), 1};
        glLoadMatrixf(viewmatrix);
}
