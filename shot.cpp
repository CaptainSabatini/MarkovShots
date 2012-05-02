#include "shot.h"

Shot::Shot()
{
    myImage = QPixmap();
    myZoom = -1;
    myVert = -1;
    myHoriz = -1;
}

Shot::Shot(QPixmap image, int zoom, int vert, int horiz)
{
    myImage = image;
    myZoom = zoom;
    myVert = vert;
    myHoriz = horiz;
}

void Shot::setImage(QPixmap image)
{myImage = image;}

void Shot::setZoom(int zoom)
{myZoom = zoom;}

void Shot::setVert(int vert)
{myVert = vert;}

void Shot::setHoriz(int horiz)
{myHoriz = horiz;}

QPixmap Shot::getImage()
{return myImage;}

int Shot::getZoom()
{return myZoom;}

int Shot::getVert()
{return myVert;}

int Shot::getHoriz()
{return myHoriz;}

bool Shot::scaleImage(int width, int height)
{
    myImage = myImage.scaled(width, height);
    return true;
}
