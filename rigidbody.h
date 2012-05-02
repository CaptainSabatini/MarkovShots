#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "matrix3f.h"
#include <GL/gl.h>

////////////////////////////////////////////
//Code adapted with permission by Alexander Festini
//http://www.flipcode.com/archives/OpenGL_Camera.shtml
////////////////////////////////////////////
/*
move and rotate come in two versions. Loc means the transformation
is in local coords, so rotating around (1,0,0) means youre rotating
around your current Right-vector while Glob would rotate around the
global x-axis.
*/

class RigidBody
{

protected:
        float Transform[16];

public:
    RigidBody(float x=0.0f, float y=0.0f, float z=0.0f);
    void moveLoc(float x, float y, float z, float distance=1);
    void moveGlob(float x, float y, float z, float distance=1);
    void rotateLoc(float deg, float x, float y, float z);
    void rotateGlob(float deg, float x, float y, float z);
    Vector3f getGlobPos() const;
    Vector3f getU();
    Vector3f getV();
    Vector3f getN();
};

#endif // RIGIDBODY_H
