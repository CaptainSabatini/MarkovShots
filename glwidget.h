#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include "camera2.h"
#include "sceneobject.h"
#include "vector3f.h"
#include <QKeyEvent>
#include <iostream>
    using std::cout;
    using std::endl;
//////////////////
//Mingw doesn't like pragma
//can't load lib fully so need to define these if undefined
//////////////////
#ifndef __in
#define __in
#endif
#ifndef __out
#define __out
#endif
#ifndef __reserved
#define __reserved
#endif
#include <XInput.h>

class GLWidget : public QGLWidget
{
    Q_OBJECT

private:
    Camera myCamera;
    SceneObject mySubject;
    SceneObject myFloor;
    Vector3f getEndsX(Vector3f list[8]);
    Vector3f getEndsY(Vector3f list[8]);
    bool isInView(Vector3f subHeight, Vector3f subWidth, float camHeight);
    int myWindowWidth;
    int myWindowHeight;

public slots:
    void keyPressEvent(QKeyEvent * event);

public:
    explicit GLWidget(QWidget *parent = 0);
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    void CheckControllerStatus();
    Vector3f getStats();

};

#endif // GLWIDGET_H
