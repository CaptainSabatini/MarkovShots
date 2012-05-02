#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cstdio>

#include "vector3f.h"
#include <iostream>
    using std::cout;
    using std::endl;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    hSrc = hDest = vSrc = vDest = zSrc = zDest =-1;
    horizData = bigTable();
    zoomData = bigTable();
    vertData = smallTable();
    firstSlot = 0;
    ui->horizTable->setItem(0, 0, new QTableWidgetItem("->", 0));
    ui->horizTable->setItem(0, 1, new QTableWidgetItem("Front", 0));
    ui->horizTable->setItem(0, 2, new QTableWidgetItem("FtLeft", 0));
    ui->horizTable->setItem(0, 3, new QTableWidgetItem("Left", 0));
    ui->horizTable->setItem(0, 4, new QTableWidgetItem("BkLeft", 0));
    ui->horizTable->setItem(0, 5, new QTableWidgetItem("Back", 0));
    ui->horizTable->setItem(0, 6, new QTableWidgetItem("BkRight", 0));
    ui->horizTable->setItem(0, 7, new QTableWidgetItem("Right", 0));
    ui->horizTable->setItem(0, 8, new QTableWidgetItem("FtRight", 0));
    ui->horizTable->setItem(1, 0, new QTableWidgetItem("Front", 0));
    ui->horizTable->setItem(2, 0, new QTableWidgetItem("FteftL", 0));
    ui->horizTable->setItem(3, 0, new QTableWidgetItem("Left", 0));
    ui->horizTable->setItem(4, 0, new QTableWidgetItem("BkLeft", 0));
    ui->horizTable->setItem(5, 0, new QTableWidgetItem("Back", 0));
    ui->horizTable->setItem(6, 0, new QTableWidgetItem("BkRight", 0));
    ui->horizTable->setItem(7, 0, new QTableWidgetItem("Right", 0));
    ui->horizTable->setItem(8, 0, new QTableWidgetItem("FtRight", 0));


    ui->zoomTable->setItem(0, 0, new QTableWidgetItem("->", 0));
    ui->zoomTable->setItem(0, 1, new QTableWidgetItem("XLong", 0));
    ui->zoomTable->setItem(0, 2, new QTableWidgetItem("Long", 0));
    ui->zoomTable->setItem(0, 3, new QTableWidgetItem("MidLong", 0));
    ui->zoomTable->setItem(0, 4, new QTableWidgetItem("Mid", 0));
    ui->zoomTable->setItem(0, 5, new QTableWidgetItem("MidClose", 0));
    ui->zoomTable->setItem(0, 6, new QTableWidgetItem("Close", 0));
    ui->zoomTable->setItem(0, 7, new QTableWidgetItem("BigClose", 0));
    ui->zoomTable->setItem(0, 8, new QTableWidgetItem("XClose", 0));
    ui->zoomTable->setItem(1, 0, new QTableWidgetItem("XLong", 0));
    ui->zoomTable->setItem(2, 0, new QTableWidgetItem("Long", 0));
    ui->zoomTable->setItem(3, 0, new QTableWidgetItem("MidLong", 0));
    ui->zoomTable->setItem(4, 0, new QTableWidgetItem("Mid", 0));
    ui->zoomTable->setItem(5, 0, new QTableWidgetItem("MidClose", 0));
    ui->zoomTable->setItem(6, 0, new QTableWidgetItem("Close", 0));
    ui->zoomTable->setItem(7, 0, new QTableWidgetItem("BigClose", 0));
    ui->zoomTable->setItem(8, 0, new QTableWidgetItem("XClose", 0));

    ui->vertTable->setItem(0, 0, new QTableWidgetItem("->", 0));
    ui->vertTable->setItem(0, 1, new QTableWidgetItem("Worm", 0));
    ui->vertTable->setItem(0, 2, new QTableWidgetItem("Low", 0));
    ui->vertTable->setItem(0, 3, new QTableWidgetItem("Eye", 0));
    ui->vertTable->setItem(0, 4, new QTableWidgetItem("High", 0));
    ui->vertTable->setItem(0, 5, new QTableWidgetItem("Bird", 0));
    ui->vertTable->setItem(1, 0, new QTableWidgetItem("Worm", 0));
    ui->vertTable->setItem(2, 0, new QTableWidgetItem("Low", 0));
    ui->vertTable->setItem(3, 0, new QTableWidgetItem("Eye", 0));
    ui->vertTable->setItem(4, 0, new QTableWidgetItem("High", 0));
    ui->vertTable->setItem(5, 0, new QTableWidgetItem("Bird", 0));

    //Set not seen tables to not visible
    ui->zoomTable->setVisible(false);
    ui->vertTable->setVisible(false);
    //Boxes were used in past for testing, information inside now used for easier updating
    //set to invisible because not needed by user
    ui->horizBox->setVisible(false);
    ui->vertBox->setVisible(false);
    ui->zoomBox->setVisible(false);
    //Label lets user know when subject is not in view in taken image, set invisible to start
    ui->informLabel->setVisible(false);
    ui->informLabel->setText("Subject not in view, no updates to tables.");

    imageSlots << ui->imageSlot0;
    imageSlots << ui->slot0Vert;
    imageSlots << ui->slot0Horiz;
    imageSlots << ui->slot0Zoom;
    imageSlots << ui->imageSlot1;
    imageSlots << ui->slot1Vert;
    imageSlots << ui->slot1Horiz;
    imageSlots << ui->slot1Zoom;
    imageSlots << ui->imageSlot2;
    imageSlots << ui->slot2Vert;
    imageSlots << ui->slot2Horiz;
    imageSlots << ui->slot2Zoom;
    imageSlots << ui->imageSlot3;
    imageSlots << ui->slot3Vert;
    imageSlots << ui->slot3Horiz;
    imageSlots << ui->slot3Zoom;
    imageSlots << ui->imageSlot4;
    imageSlots << ui->slot4Vert;
    imageSlots << ui->slot4Horiz;
    imageSlots << ui->slot4Zoom;
    imageSlots << ui->imageSlot5;
    imageSlots << ui->slot5Vert;
    imageSlots << ui->slot5Horiz;
    imageSlots << ui->slot5Zoom;
    imageSlots << ui->imageSlot6;
    imageSlots << ui->slot6Vert;
    imageSlots << ui->slot6Horiz;
    imageSlots << ui->slot6Zoom;
    imageSlots << ui->imageSlot7;
    imageSlots << ui->slot7Vert;
    imageSlots << ui->slot7Horiz;
    imageSlots << ui->slot7Zoom;
    curTable = 0;

    for(int i(0); i < imageSlots.size(); i++)
    {
        imageSlots[i]->clear();
    }

    fillTables();
    controlTimer = new QTimer(this);
    connect(controlTimer, SIGNAL(timeout()), this, SLOT(controllerStateHandler()));
    controlTimer->start(50);

    buttonTimer = new QTimer(this);
    connect(buttonTimer, SIGNAL(timeout()), this, SLOT(buttonHeldHandler()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::buttonClickedHandler()
{
    if(hSrc<0)
    {
        hSrc = ui->horizBox->currentIndex();
        vSrc = ui->vertBox->currentIndex();
        zSrc = ui->zoomBox->currentIndex();
    }
    else
    {
        if(hDest>=0)
        {
            hSrc = hDest;
            vSrc = vDest;
            zSrc = zDest;
        }
        hDest = ui->horizBox->currentIndex();
        vDest = ui->vertBox->currentIndex();
        zDest = ui->zoomBox->currentIndex();
        horizData.add(hSrc, hDest);
        vertData.add(vSrc, vDest);
        zoomData.add(zSrc, zDest);
        fillTables();
    }
}

void MainWindow::controllerStateHandler()
{
    ui->widget->CheckControllerStatus();

    //Used to store if a controller is connected
    DWORD dwResult;
    //Data type that stores all the current states of a controller
    XINPUT_STATE state;

    //Zeros out the states of the controller.
    ZeroMemory( &state, sizeof(XINPUT_STATE) );

    //Get all the current states of controller 1
    dwResult = XInputGetState( 0, &state );

    if( dwResult == ERROR_SUCCESS )
    {
    //Controller is connected.
        //if a button is pressed and it is A
        if(state.Gamepad.wButtons & XINPUT_GAMEPAD_A)
        {
            keyPressEvent(new QKeyEvent(QEvent::KeyPress, Qt::Key_Q, Qt::NoModifier));
            controlTimer->stop();
            buttonTimer->start(100);
        }
        if(state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
        {
            leftShiftClickedHandler();
        }
        if(state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
        {
            rightShiftClickedHandler();
        }
        if(state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK)
        {
            changeTable();
            controlTimer->stop();
            buttonTimer->start(100);
        }
    }
    //else NOT CONNECTED
}

void MainWindow::changeTable()
{
    int table = (++curTable)%3;
    cout << curTable << endl;
    switch(table)
    {
        case 0: horizClickedHandler();
        break;
        case 1: vertClickedHandler();
        break;
        case 2: zoomClickedHandler();
    }
}

void MainWindow::buttonHeldHandler()
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
        if(!(state.Gamepad.wButtons & XINPUT_GAMEPAD_A) && !(state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK))
        {
            buttonTimer->stop();
            controlTimer->start(50);
        }
    }
    else
    {
        //cout << "NOT CONNECTED!" << endl;
    }
}

void MainWindow::fillImages()
{
    int i = firstSlot;
    int spot = 0;
    while(i<images.size() && spot<imageSlots.size())
    {
        //Image
        imageSlots[spot++]->setPixmap(images[i].getImage());
        //Vert
        imageSlots[spot++]->setText(getVertLabel(images[i].getVert()));
        //Horiz
        imageSlots[spot++]->setText(getHorizLabel(images[i].getHoriz()));
        //Zoom
        imageSlots[spot++]->setText(getZoomLabel(images[i++].getZoom()));
    }
    while(spot<imageSlots.size())
    {
        imageSlots[spot++]->clear();
        imageSlots[spot++]->setText("No Image");
        imageSlots[spot++]->setText("No Image");
        imageSlots[spot++]->setText("No Image");
    }
}

void MainWindow::fillTables()
{
    char msg[64];
    for(int r(0); r < 8; r++)
            for(int c(0); c < 8; c++)
            {
                sprintf (msg, "%f", horizData.getMarkov(r, c));
                ui->horizTable->setItem(r+1, c+1, new QTableWidgetItem(QString(msg), 0));
            }
    for(int r(0); r < 8; r++)
                for(int c(0); c < 8; c++)
                {
                    sprintf (msg, "%f", zoomData.getMarkov(r, c));
                    ui->zoomTable->setItem(r+1, c+1, new QTableWidgetItem(QString(msg), 0));
                }
    for(int r(0); r < 5; r++)
                for(int c(0); c < 5; c++)
                {
                     sprintf (msg, "%f", vertData.getMarkov(r, c));
                     ui->vertTable->setItem(r+1, c+1, new QTableWidgetItem(QString(msg), 0));
                 }
}

void MainWindow::horizClickedHandler()
{
    ui->actionHorizontal->setChecked(true);
    ui->actionVertical->setChecked(false);
    ui->actionZoom->setChecked(false);
    ui->zoomTable->setVisible(false);
    ui->horizTable->setVisible(true);
    ui->vertTable->setVisible(false);
}

void MainWindow::zoomClickedHandler()
{
    ui->actionHorizontal->setChecked(false);
    ui->actionVertical->setChecked(false);
    ui->actionZoom->setChecked(true);
    ui->zoomTable->setVisible(true);
    ui->horizTable->setVisible(false);
    ui->vertTable->setVisible(false);
}

void MainWindow::vertClickedHandler()
{
    ui->actionHorizontal->setChecked(false);
    ui->actionVertical->setChecked(true);
    ui->actionZoom->setChecked(false);
    ui->zoomTable->setVisible(false);
    ui->horizTable->setVisible(false);
    ui->vertTable->setVisible(true);
}

void MainWindow::leftShiftClickedHandler()
{
    if(firstSlot > 0)
    {
        firstSlot--;
        fillImages();
    }
    if(firstSlot == 0)
        ui->imagesLeftButton->setEnabled(false);
    if(firstSlot+7 >= (images.size()-1))
        ui->imagesRightButton->setEnabled(false);
    else
        ui->imagesRightButton->setEnabled(true);
}

void MainWindow::rightShiftClickedHandler()
{
    if(firstSlot+7 < (images.size()-1))
    {
        firstSlot++;
        fillImages();
    }
    //firstSlot == (images.size()-1)
    if(firstSlot+7 >= (images.size()-1))
        ui->imagesRightButton->setEnabled(false);
    if(firstSlot == 0)
        ui->imagesLeftButton->setEnabled(false);
    else
        ui->imagesLeftButton->setEnabled(true);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    ui->widget->keyPressEvent(event);
    if(event->key() == Qt::Key_Q)
    {
        ui->informLabel->setVisible(false);
        Vector3f shotSpecs = ui->widget->getStats();
        images << Shot(ui->widget->renderPixmap(), shotSpecs.getZ(), shotSpecs.getY(), shotSpecs.getX());
        images.last().scaleImage(ui->imageSlot0->width(), ui->imageSlot0->height());
        if(firstSlot+7 < (images.size()-1))
            ui->imagesRightButton->setEnabled(true);
        fillImages();
        //X horiz, Y vert, Z
        if(shotSpecs.getX() > -1)
        {
            if(hSrc<0)
            {
                hSrc = getHoriz(shotSpecs.getX());
                vSrc = shotSpecs.getY();
                zSrc = shotSpecs.getZ();
            }
            else
            {
                if(hDest>=0)
                {
                    hSrc = hDest;
                    vSrc = vDest;
                    zSrc = zDest;
                }
                hDest = getHoriz(shotSpecs.getX());
                vDest = shotSpecs.getY();
                zDest = shotSpecs.getZ();
                horizData.add(hSrc, hDest);
                vertData.add(vSrc, vDest);
                zoomData.add(zSrc, zDest);
                fillTables();
            }
        }//If Is In View
        else
            ui->informLabel->setVisible(true);
    }
}

int MainWindow::getHoriz(int horiz)
{
    //{FRONT = 5, BACK = 3, LEFT = 6, RIGHT = 7, FR = 12, FL = 11, BR = 10, BL = 9}
    //cout << "DIRECTION: " << horiz << endl;
    int pos(0);
    switch(horiz)
    {
        case FRONT: pos = 0;
            break;
        case FL: pos = 1;
            break;
        case LEFT: pos = 2;
            break;
        case BL: pos = 3;
            break;
        case BACK: pos = 4;
            break;
        case BR: pos = 5;
            break;
        case RIGHT: pos = 6;
            break;
        case FR: pos = 7;
            break;
    }
    return pos;
}

QString MainWindow::getVertLabel(int i)
{

    //VERT
    /////////////////////////
    //Worm  0
    //Low   1
    //Eye   2
    //High  3
    //Bird  4
    //////////////////////////

    QString text;
    switch(i)
    {
    case 0: text = "Worm";
        break;
    case 1: text = "Low";
        break;
    case 2: text = "Eye";
        break;
    case 3: text = "High";
        break;
    case 4: text = "Bird";
        break;
    default: text = "No Subject";
    }
    return text;
}

QString MainWindow::getHorizLabel(int i)
{

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

    QString text;
    switch(i)
    {
    case 3: text = "Front";
        break;
    case 9: text = "FtR";
        break;
    case 10: text = "FtL";
        break;
    case 6: text = "Right";
        break;
    case 7: text = "Left";
        break;
    case 5: text = "Back";
        break;
    case 11: text = "BkR";
        break;
    case 12: text = "BkL";
        break;
    default: text = "No Subject";
    }
    return text;
}

QString MainWindow::getZoomLabel(int i)
{

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

    QString text;
    switch(i)
    {
    case 0: text = "XL";
        break;
    case 1: text = "LS";
        break;
    case 2: text = "ML";
        break;
    case 3: text = "MS";
        break;
    case 4: text = "MCU";
        break;
    case 5: text = "CU";
        break;
    case 6: text = "BCU";
        break;
    case 7: text = "XCU";
        break;
    default: text = "No Subject";
    }
    return text;
}
