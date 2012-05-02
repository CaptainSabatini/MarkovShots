#include "sceneobject.h"
#include <math.h>


SceneObject::SceneObject(float x, float y, float z)
{
    for(int i(0); i< BOXSIZE; i++)
        myBBox[i] = Vector3f();
    for(int i(0); i<16; i++)
        {Transform[i] = 0;}

    Transform[0] = 1.0f;
    Transform[5] = 1.0f;
    Transform[10] = -1.0f;
    Transform[15] = 1.0f;
    Transform[12] = x; Transform[13] = y; Transform[14] = z;
}

/*SceneObject::SceneObject(SceneObject& source)
{
    for(int i(0); i< BOXSIZE; i++)
        myBBox[i] = source.getBoundAt(i);
    myUp = source.getUp();
    myRight = source.getRight();
    myAim = source.getAim();
    myPos = source.getPos();
}*/

///////////////////////////////////////////
//getBox
//Returns the array of bounding points as a pointer
//Input: void
//Output: pointer to a Point
///////////////////////////////////////////
Vector3f* SceneObject::getBoundBox()
{return myBBox;}

///////////////////////////////////////////
//getBoundAt
//Returns one of the points as requested
//Input: int bound, which element to return
//Output: the Point at desired element
///////////////////////////////////////////
Vector3f SceneObject::getBoundAt(int bound)
{
    return myBBox[bound];
}

void SceneObject::drawObject(const int shapeType)
{
    enum SHAPE {CUBE, CYLINDER, FLOOR};
    glPushMatrix();
    {
        glTranslatef(Transform[12], Transform[13], Transform[14]);
        switch(shapeType)
        {
            case CUBE: drawCube();
                break;
            case CYLINDER: drawCylinder();
                break;
            case FLOOR: drawFloor();
                break;
        }
    }glPopMatrix();
}

void SceneObject::drawCube()
{
    glPushMatrix();
    {
    float pts[8][3] = {{-2, 2, -2},// 0
                                    {2,2,-2},// 1
                                    {-2,-2,-2},// 2
                                    {2,-2,-2},// 3
                                    {2,2,2},// 4
                                    {2,-2,2},// 5
                                    {-2,2,2},// 6
                                    {-2,-2,2}};// 7
    for(int i(0); i< BOXSIZE; i++)
        myBBox[i].set(pts[i][0], pts[i][1], pts[i][2]);

            glBegin(GL_QUADS);
            glColor3f(0, 1.0, 0);
            glVertex3fv(pts[4]);
            glVertex3fv(pts[6]);
            glVertex3fv(pts[7]);
            glVertex3fv(pts[5]);
            //Back
            glColor3f(1.0, 1.0, 0);
            glVertex3fv(pts[2]);
            glVertex3fv(pts[3]);
            glVertex3fv(pts[5]);
            glVertex3fv(pts[7]);
            //Bottom
            glColor3f(1.0, 0, 1.0);
            glVertex3fv(pts[6]);
            glVertex3fv(pts[0]);
            glVertex3fv(pts[2]);
            glVertex3fv(pts[7]);
            //Left
            glColor3f(0, 0, 1.0);
            glVertex3fv(pts[4]);
            glVertex3fv(pts[5]);
            glVertex3fv(pts[3]);
            glVertex3fv(pts[1]);
            //Right
            glColor3f(0, 1.0, 1.0);
            glVertex3fv(pts[0]);
            glVertex3fv(pts[6]);
            glVertex3fv(pts[4]);
            glVertex3fv(pts[1]);
            //Top
            glColor3f(1.0, 0, 0);
            glVertex3fv(pts[0]);
            glVertex3fv(pts[1]);
            glVertex3fv(pts[3]);
            glVertex3fv(pts[2]);
            //Front
            glEnd();
    }glPopMatrix();

}

void SceneObject::drawCylinder()
{

    glShadeModel(GL_FLAT);

    float bottom[8][3] = {{1, 0, 0},// 0
                            {1/sqrt(2.0f),-1/sqrt(2.0f),0},// 1
                            {0,-1,0},// 2
                            {-1/sqrt(2.0f),-1/sqrt(2.0f),0},// 3
                            {-1,0,0},// 4
                            {-1/sqrt(2.0f),1/sqrt(2.0f),0},// 5
                            {0,1,0},// 6
                            {1/sqrt(2.0f),1/sqrt(2.0f),0}};// 7
    float top[8][3] = {{1, 1, 0},// 0
                            {1/sqrt(2.0f),1/sqrt(2.0f),1},// 1
                            {0,1,1},// 2
                            {-1/sqrt(2.0f),1/sqrt(2.0f),1},// 3
                            {-1,0,1},// 4
                            {-1/sqrt(2.0f),-1/sqrt(2.0f),1},// 5
                            {0,-1,1},// 6
                            {1/sqrt(2.0f),-1/sqrt(2.0f),1}};// 7
    glNormal3f(0, 0, -1);
    glBegin(GL_TRIANGLE_FAN);
            glVertex3f(0, 0, 0);
            for(int i(0); i < 8; i++)
                    glVertex3fv(bottom[i]);
            glVertex3fv(bottom[0]);
    glEnd();
    glNormal3f(0, 0, 1);
    glBegin(GL_TRIANGLE_FAN);
            glVertex3f(0, 0, 1);
            for(int i(0); i < 8; i++)
                    glVertex3fv(top[i]);
            glVertex3fv(top[0]);
    glEnd();
    /*	Top	Bottom
            0	0
            1	7
            2	6
            3	5
            4	4
            5	3
            6	2
            7	1
    */
    glShadeModel(GL_SMOOTH);
    glBegin(GL_QUAD_STRIP);
            //
            glVertex3fv(top[0]);
            glVertex3fv(bottom[0]);

            glVertex3fv(top[1]);
            glVertex3fv(bottom[7]);


            //
            glVertex3fv(top[2]);
            glVertex3fv(bottom[6]);

            glVertex3fv(top[3]);
            glVertex3fv(bottom[5]);

            glVertex3fv(top[4]);
            glVertex3fv(bottom[4]);

            //
            glVertex3fv(top[5]);
            glVertex3fv(bottom[3]);
            glColor3f(1, .5, .5);

            glVertex3fv(top[6]);
            glVertex3fv(bottom[2]);

            glVertex3fv(top[7]);
            glVertex3fv(bottom[1]);

            glVertex3fv(top[0]);
            glVertex3fv(bottom[0]);
    glEnd();

}

void SceneObject::drawFloor()
{

    float numStepsX = 20;
    float numStepsZ = 20;
    glShadeModel(GL_FLAT);

    glColor3f(.98, .9, .78);
    glBegin(GL_QUADS);
        glVertex3f(numStepsX/2, 0, numStepsZ/2);
        glVertex3f(-numStepsX/2, 0, numStepsZ/2);
        glVertex3f(-numStepsX/2, 0, -numStepsZ/2);
        glVertex3f(numStepsX/2, 0, -numStepsZ/2);
    glEnd();

    //Draw floor again so it is seen from top AND bottom
    glBegin(GL_QUADS);
        glVertex3f(numStepsX/2, 0, numStepsZ/2);
        glVertex3f(numStepsX/2, 0, -numStepsZ/2);
        glVertex3f(-numStepsX/2, 0, -numStepsZ/2);
        glVertex3f(-numStepsX/2, 0, numStepsZ/2);
    glEnd();

    glPushMatrix();
    {//PUSHED

        //Push the grid slightly up the Y-axis to stop colliding in Z-Buffer
        glTranslatef(0, .025, 0);

        glPushMatrix();
        {//PUSHED
            glTranslatef(0, 0, numStepsX/2);
            for(int i(numStepsX); i >= 0; i--)
            {
                    if(i == numStepsX/2)
                            glColor3f(0.0, 1.0, 0);
                    else
                            glColor3f(1.0, 1.0, 1.0);
                    drawGridLine(numStepsZ/2);
                    glTranslatef(0, 0, -1);
            }
        glPopMatrix();}//POPPED
        glPushMatrix();//PUSHED
        {
            glRotatef(90, 0, 1, 0);
            //drawGridLine(numStepsX);
            //glPushMatrix();
            glTranslatef(0, 0, numStepsZ/2);
            for(int i(numStepsZ); i >= 0; i--)
            {
                if(i == numStepsZ/2)
                        glColor3f(1.0, 0, 0);
                else
                        glColor3f(1.0, 1.0, 1.0);
                drawGridLine(numStepsX/2);
                glTranslatef(0, 0, -1);
            }
        glPopMatrix();}//POPPED
    glPopMatrix();}//POPPED
}

void SceneObject::drawGridLine(float length)
{
        glColor3f(0, 0, 0);
        glBegin(GL_LINES);
                glVertex3f(-length, 0, 0);
                glVertex3f(length, 0, 0);
        glEnd();
}

float SceneObject::getLargeX()
{
    float max = myBBox[0].getX();
    for(int i(0); i< BOXSIZE; i++)
        if(myBBox[i].getX() > max)
            max = myBBox[i].getX();
    return max;
}

float SceneObject::getSmallX()
{
    float min = myBBox[0].getX();
    for(int i(0); i< BOXSIZE; i++)
        if(myBBox[i].getX() < min)
            min = myBBox[i].getX();
    return min;
}

float SceneObject::getLargeY()
{
    float max = myBBox[0].getY();
    for(int i(0); i< BOXSIZE; i++)
        if(myBBox[i].getY() > max)
            max = myBBox[i].getY();
    return max;
}

float SceneObject::getSmallY()
{
    float min = myBBox[0].getY();
    for(int i(0); i< BOXSIZE; i++)
        if(myBBox[i].getY() < min)
            min = myBBox[i].getY();
    return min;
}

float SceneObject::getLargeZ()
{
    float max = myBBox[0].getZ();
    for(int i(0); i< BOXSIZE; i++)
        if(myBBox[i].getZ() > max)
            max = myBBox[i].getZ();
    return max;
}

float SceneObject::getSmallZ()
{
    float min = myBBox[0].getZ();
    for(int i(0); i< BOXSIZE; i++)
        if(myBBox[i].getZ() < min)
            min = myBBox[i].getZ();
    return min;
}

float SceneObject::getWidth()
{
    return(getLargeX() - getSmallX());
}

float SceneObject::getHeight()
{
    return(getLargeY() - getSmallY());
}

float SceneObject::getDepth()
{
    return(getLargeZ() - getSmallZ());
}

void SceneObject::getGlobBox(Vector3f setup[8])
{

    for(int i(0); i<8; i++)
    {
        setup[i] = Vector3f();
    }

    for(int i(0); i < BOXSIZE; i++)
    {
        setup[i].set(myBBox[i].getX()*Transform[0] + myBBox[i].getY()*Transform[4] + myBBox[i].getZ()*Transform[8] + Transform[12],
                     myBBox[i].getX()*Transform[1] + myBBox[i].getY()*Transform[5] + myBBox[i].getZ()*Transform[9] + Transform[13],
                     myBBox[i].getX()*Transform[2] + myBBox[i].getY()*Transform[6] + myBBox[i].getZ()*Transform[10] + Transform[14]);
    }
}
