#ifndef SHOT_H
#define SHOT_H

#include <QPixmap>

class Shot
{
private:
    int myZoom;
    int myVert;
    int myHoriz;
    QPixmap myImage;

public:
    Shot();
    Shot(QPixmap image, int zoom = -1, int vert = -1, int horiz = -1);
    void setImage(QPixmap image);
    void setZoom(int zoom);
    void setVert(int vert);
    void setHoriz(int horiz);
    QPixmap getImage();
    int getZoom();
    int getVert();
    int getHoriz();
    bool scaleImage(int width, int height);
};

#endif // SHOT_H
