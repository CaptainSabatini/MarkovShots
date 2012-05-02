#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "bigTable.h"
#include "smallTable.h"
#include "shot.h"
#include <sstream>
#include <QTimer>
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

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void buttonClickedHandler();
    void horizClickedHandler();
    void vertClickedHandler();
    void zoomClickedHandler();
    void keyPressEvent(QKeyEvent *event);
    void leftShiftClickedHandler();
    void rightShiftClickedHandler();
    void controllerStateHandler();
    void buttonHeldHandler();

private:
    Ui::MainWindow *ui;
    QPixmap test;
    /////////////////////////
    //Front Right   9
    //Front Left    1
    //Back Right    11
    //Back Left     12
    //////////////////////////
    enum horizEnum {FRONT = 3, BACK = 5, LEFT = 7, RIGHT = 6, FR = 9, FL = 10, BR = 11, BL = 12};
    enum vertEnum {WORM, LOW, EYE, HIGH, BIRD};
    QList<QLabel*> imageSlots;
    QList<Shot> images;
    int firstSlot;
    int hSrc;
    int hDest;
    int vSrc;
    int vDest;
    int zSrc;
    int zDest;
    int curTable;
    bigTable horizData;
    bigTable zoomData;
    smallTable vertData;
    enum {HORIZTABLE = 0, VERTTABLE = 1, ZOOMTABLE = 2};
    void fillTables();
    void fillImages();
    int getHoriz(int horiz);
    QString getVertLabel(int i);
    QString getHorizLabel(int i);
    QString getZoomLabel(int i);
    QTimer *controlTimer;
    QTimer *buttonTimer;
    void changeTable();
};

#endif // MAINWINDOW_H
