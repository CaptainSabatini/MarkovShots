////////////////////////////////////////////
//Code adapted with permission by Alexander Festini
//http://www.flipcode.com/archives/OpenGL_Camera.shtml
////////////////////////////////////////////

#include "rigidbody.h"
#include <iostream>
    using std::cout;
    using std::endl;

RigidBody::RigidBody(float x, float y, float z)
{
    for(int i(0); i<16; i++)
        {Transform[i] = 0;}

    Transform[0] = 1.0f;
    Transform[5] = 1.0f;
    Transform[10] = 1.0f;
    Transform[15] = 1.0f;
    Transform[12] = x; Transform[13] = y; Transform[14] = z;
}

void RigidBody::moveLoc(float x, float y, float z, float distance) {
        float dx=x*Transform[0] + y*Transform[4] + z*Transform[8];
        float dy=x*Transform[1] + y*Transform[5] + z*Transform[9];
        float dz=x*Transform[2] + y*Transform[6] + z*Transform[10];
        Transform[12] += dx * distance;
        Transform[13] += dy * distance;
        Transform[14] += dz * distance;
}

void RigidBody::moveGlob(float x, float y, float z, float distance) {
        Transform[12] += x * distance;
        Transform[13] += y * distance;
        Transform[14] += z * distance;
}

/*
Here we let OpenGl functions do the work.
*/
void RigidBody::rotateLoc(float deg, float x, float y, float z) {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadMatrixf(Transform);
        glRotatef(deg, x,y,z);
        glGetFloatv(GL_MODELVIEW_MATRIX, Transform);
        glPopMatrix();
}

/*
We have to invert the rotations to get the global axes in local coords.
*/
void RigidBody::rotateGlob(float deg, float x, float y, float z) {
        float dx=x*Transform[0] + y*Transform[1] + z*Transform[2];
        float dy=x*Transform[4] + y*Transform[5] + z*Transform[6];
        float dz=x*Transform[8] + y*Transform[9] + z*Transform[10];
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadMatrixf(Transform);
        glRotatef(deg, dx,dy,dz);
        glGetFloatv(GL_MODELVIEW_MATRIX, Transform);
        glPopMatrix();
}

Vector3f RigidBody::getGlobPos() const
{
    return(Vector3f(Transform[12], Transform[13], Transform[14]));
}

Vector3f RigidBody::getU()
{
    return(Vector3f(Transform[0], Transform[1], Transform[2]));
}

Vector3f RigidBody::getV()
{
    return(Vector3f(Transform[4], Transform[5], Transform[6]));
}

Vector3f RigidBody::getN()
{
    return(Vector3f(Transform[8], Transform[9], Transform[10]));
}
