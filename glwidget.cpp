#include "glwidget.h"
#include "vector3f.h"
#include <cmath>
#include <iostream>
    using std::cout;
    using std::endl;

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    myCamera = Camera(0, 2, 20, 30, 1, 1, 1000);
    mySubject = SceneObject(0, 2, 0);
    myFloor = SceneObject();
}

void GLWidget::initializeGL()
{
    glClearColor(1, 1, 1, 1);
}

void GLWidget::paintGL()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(myCamera.getFOV(), myCamera.getAspect(), myCamera.getNearZ(), myCamera.getFarZ());
    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    myCamera.setView();


    myFloor.drawObject(2);
    mySubject.drawObject(0);


}

void GLWidget::CheckControllerStatus()
{    
    DWORD dwResult;         // Used to store if a controller is connected
    XINPUT_STATE state;     // Data type that stores all the current states
                // of a controller.

    ZeroMemory( &state, sizeof(XINPUT_STATE) ); // Zeros out the states of
                                          // the controller.

    // Get all the current states of controller 1
    dwResult = XInputGetState( 0, &state );

    if( dwResult == ERROR_SUCCESS )
    {
    // Controller is connected.
    // -----------INSERT BUTTON CHECKS HERE----------
        {
          if(state.Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
              keyPressEvent(new QKeyEvent(QEvent::KeyPress, Qt::Key_S, Qt::NoModifier));
          else
              if(state.Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
                  keyPressEvent(new QKeyEvent(QEvent::KeyPress, Qt::Key_W, Qt::NoModifier));
        }//Left Y Axis
        {
          if(state.Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
              keyPressEvent(new QKeyEvent(QEvent::KeyPress, Qt::Key_A, Qt::NoModifier));
          else
              if(state.Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
                  keyPressEvent(new QKeyEvent(QEvent::KeyPress, Qt::Key_D, Qt::NoModifier));
        }//Left X Axis
        {
          if(state.Gamepad.sThumbRY < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
              keyPressEvent(new QKeyEvent(QEvent::KeyPress, Qt::Key_K, Qt::NoModifier));
          else
              if(state.Gamepad.sThumbRY > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
                  keyPressEvent(new QKeyEvent(QEvent::KeyPress, Qt::Key_I, Qt::NoModifier));
        }//Right Y Axis
        {
          if(state.Gamepad.sThumbRX < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
              keyPressEvent(new QKeyEvent(QEvent::KeyPress, Qt::Key_J, Qt::NoModifier));
          else
              if(state.Gamepad.sThumbRX > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
                  keyPressEvent(new QKeyEvent(QEvent::KeyPress, Qt::Key_L, Qt::NoModifier));
        }//RIGHT X Axis
        {
          if(state.Gamepad.bRightTrigger >0)
              keyPressEvent(new QKeyEvent(QEvent::KeyPress, Qt::Key_R, Qt::NoModifier));
          if(state.Gamepad.bLeftTrigger > 0)
              keyPressEvent(new QKeyEvent(QEvent::KeyPress, Qt::Key_F, Qt::NoModifier));
        }//Triggers
    }
    else
    {
        //cout << "NOT CONNECTED!" << endl;
    }
}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    gluOrtho2D(0,w, 0,h);
    paintGL();
}


void GLWidget::keyPressEvent(QKeyEvent *event)
{
    //UP   0
    //Down 1
    //Left 2
    //Right 3
    //Forward 4
    //Backward 5
    switch(event->key())
        {
            case Qt::Key_S:
                myCamera.moveLoc(0, 0, 1, .25);
                break;
            case Qt::Key_W:
                myCamera.moveLoc(0, 0, 1, -.25);
                break;
            case Qt::Key_A:
                myCamera.moveLoc(1, 0, 0, -.25);
                break;
            case Qt::Key_D:
                myCamera.moveLoc(1, 0, 0, .25);
                break;
            case Qt::Key_R:
                myCamera.moveLoc(0, 1, 0, .25);
                break;
            case Qt::Key_F:
                myCamera.moveLoc(0, 1, 0, -.25);
                break;
                //
                //Move Aim
                //
            case Qt::Key_I:
                myCamera.rotateLoc(1, 1, 0, 0);
                break;
            case Qt::Key_K:
                myCamera.rotateLoc(1, -1, 0, 0);
                break;
            case Qt::Key_L:
                myCamera.rotateGlob(1, 0, -1, 0);
                break;
            case Qt::Key_J:
                myCamera.rotateGlob(1, 0, 1, 0);
                break;
        }
        updateGL();
}

Vector3f GLWidget::getStats()
{
    Vector3f camPos = myCamera.getGlobPos();
    Vector3f subPos = mySubject.getGlobPos();
    float x, y, z;
    x = y = z = 0;
    Vector3f bound[8];
    Vector3f pro2D[8];
    Vector3f myStats = Vector3f(-1, -1, -1);//default to NOT IN VIEW
    mySubject.getGlobBox(bound);
    myCamera.get2DProjection(bound, pro2D);
    if(myCamera.isInView(bound))
    {
        Vector3f endsY = getEndsY(pro2D);
        //Vector3f endsX = getEndsX(pro2D);
        float camHeight = myCamera.getHeightAt(myCamera.getNearZ());
            //HORIZ

            /////////////////////////
            //Front         3
            //Front Right   9
            //Front Left    1
            //Right         6
            //Left          7
            //Back          5
            //Back Right    11
            //Back Left     12
            //////////////////////////
            //
            //REMINDER: Looking down -Z as "Forward" means -X is right, +X is left
            //
            if(camPos.getX() >= subPos.getX() + mySubject.getWidth()/2)
                x += 7;
                else if(camPos.getX() <= subPos.getX() - mySubject.getWidth()/2)
                    x += 6;
            if(camPos.getZ() >= subPos.getZ() + mySubject.getDepth()/2)
                x += 3;
                else if(camPos.getZ() <= subPos.getZ() - mySubject.getDepth()/2)
                    x += 5;


            //VERT
            /////////////////////////
            //Worm  0
            //Low   1
            //Eye   2
            //High  3
            //Bird  4
            //////////////////////////

            if(camPos.getY() <= subPos.getY() + mySubject.getHeight()/2
                    &&camPos.getY() >= subPos.getY() - mySubject.getHeight()/2)
                    y = 2;
            else
                if(camPos.getY() > subPos.getY() + mySubject.getHeight()/2
                        &&camPos.getY() < subPos.getY()+ mySubject.getHeight()/2 + mySubject.getHeight())
                    y = 3;
                else
                    if(camPos.getY() >= subPos.getY()+ mySubject.getHeight()/2 + mySubject.getHeight())
                        y = 4;
            else
                        if(camPos.getY() < subPos.getY() - mySubject.getHeight()/2
                                &&camPos.getY() > subPos.getY() - mySubject.getHeight()/2 - mySubject.getHeight())
                            y = 1;
            else
                            y = 0;

            //ZOOM
            /////////////////////////
            //XL        0
            //LS        1
            //ML        2
            //MS        3
            //MCU       4
            //CU        5
            //BCU       6
            //XCU       7
            //////////////////////////
            float heightRatio = 0;
            float height = endsY.getX() - endsY.getY();
            //Just to make sure not dividing by zero
            if(camHeight)
                heightRatio = height/camHeight;

            //Large nested if-else because ranges
            {
            if(heightRatio <= 1/(10.0))
                z= 0;
            else
                if(heightRatio <= 1/(6.0))
                    z = 1;
                    else
                    if(heightRatio <= 1/(3.0))
                        z = 2;
                    else
                        if(heightRatio <= 1/(2.0))
                            z = 3;
                        else
                            if(heightRatio <= 2.0/3.0)
                                z = 4;
                            else
                                if(heightRatio <= 9/10.0)
                                    z = 5;
                                else
                                    if(heightRatio <= 1.5)
                                        z = 6;
                                    else
                                            z = 7;
            }
            myStats = Vector3f(x, y, z);
    }//isInView
    return myStats;
}

Vector3f GLWidget::getEndsX(Vector3f list[8])
{
    float high(list[0].getX());
    float low(list[0].getX());
    for(int i(1) ; i<8; i++)
    {
        if(high < list[i].getX())
            high = list[i].getX();
        if(low > list[i].getX())
            low = list[i].getX();
    }
    //cout << "LowX: " << low << " HighX: " << high << endl;
    return Vector3f(high, low, 0);
}

Vector3f GLWidget::getEndsY(Vector3f list[8])
{
    float high(list[0].getY());
    float low(list[0].getY());
   // for(int i(0); i < 8; i++)
    //{
        //cout << "X" << i <<": " << list[i].getX() << " Y" << i <<": " << list[i].getY() << " Z" << i <<": " << list[i].getZ() << endl;
    //}
    for(int i(1) ; i<8; i++)
    {
        if(high < list[i].getY())
            high = list[i].getY();
        if(low > list[i].getY())
            low = list[i].getY();
    }
    //cout << "LowY: " << low << " HighY: " << high << endl;
    return Vector3f(high, low, 0);
}

bool GLWidget::isInView(Vector3f subHeight, Vector3f subWidth, float camHeight)
{
    bool flag = (subHeight.getX() < -1*camHeight/2
                 || subHeight.getY() > camHeight/2);
    if(!flag)
        flag = (subWidth.getX() < -1*myCamera.getAspect()*camHeight/2
                         || subWidth.getY() > myCamera.getAspect()*camHeight/2);
    return !flag;

}
