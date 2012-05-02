#include "matrix3f.h"
#include "Vector3f.h"
#include <math.h>


/*
  *Default Constructor, calls identity
  */
Matrix3f::Matrix3f()
{
    identity();
}//defualt const

/*
  * Copy Constructor
  */
Matrix3f::Matrix3f(const Matrix3f& source)
{
    for(int r(0); r<mySize; r++)
        for(int c(0); c<mySize; c++)
            myMatrix[r][c] = source.getElement(r, c);
}//Copy const
/*
  * Changes the matrix into identity matrix
  */
void Matrix3f::identity()
{
    for(int r(0); r<mySize; r++)
        for(int c(0); c<mySize; c++)
            if(r == c)
                myMatrix[r][c] = 1.0;
            else
                myMatrix[r][c]=0.0;
}//identity

void Matrix3f::setRow(const int row, const Vector3f source)
{
    myMatrix[row][0] = source.getX();
    myMatrix[row][1] = source.getY();
    myMatrix[row][2] = source.getZ();
}

void Matrix3f::setCol(const int col, const Vector3f source)
{
    myMatrix[0][col] = source.getX();
    myMatrix[1][col] = source.getY();
    myMatrix[2][col] = source.getZ();
    myMatrix[3][3] = 1.0;
}

/*
  * Changes the matrix into a translate matrix
  */
void Matrix3f::translate(const float tx,  const float ty, const float tz)
{
    identity();
    myMatrix[3][0] = tx;
    myMatrix[3][1] = ty;
    myMatrix[3][2] = tz;
}//translate

/*
  * Changes the matrix into a scale matrix
  */
void Matrix3f::scale(const float sx, const float sy, const float sz)
{
    identity();
    myMatrix[0][0] = sx;
    myMatrix[1][1] = sy;
    myMatrix[2][2] = sz;
}//scale

/*
  * Changes the matrix into a rotate matrix
  */
void Matrix3f::rotate(const float theta, int axis)
{
    identity();
    switch(axis)
    {
    case X:
        myMatrix[1][1] = cos(theta);
        myMatrix[1][2] = -1*sin(theta);
        myMatrix[2][2] = cos(theta);
        myMatrix[2][1] = sin(theta);
        break;
    case Y:
        myMatrix[0][0] = cos(theta);
        myMatrix[2][0] = -1*sin(theta);
        myMatrix[2][2] = cos(theta);
        myMatrix[0][2] = sin(theta);
        break;
    case Z:
        myMatrix[0][0] = cos(theta);
        myMatrix[0][1] = -1*sin(theta);
        myMatrix[1][1] = cos(theta);
        myMatrix[1][0] = sin(theta);
    }

}//rotate

/*
  *Receives two points by reference, an input point and an output point
  *Multiplies the point by the (net) matrix places the new values
  *into output point
  */
void Matrix3f::transformPoint(Vector3f& outPt, const Vector3f& inPt)
{
    float x = inPt.getX();
    float y = inPt.getY();
    float z = inPt.getZ();
    //print();
    x = (myMatrix[0][0]*x + myMatrix[1][0]*y+ myMatrix[2][0]*z + myMatrix[3][0]);
    y = (myMatrix[0][1]*x + myMatrix[1][1]*y+ myMatrix[2][1]*z + myMatrix[3][1]);
    z = (myMatrix[0][2]*x + myMatrix[1][2]*y+ myMatrix[2][2]*z + myMatrix[3][2]);
    outPt.set(x,y, z);
}//transform

/*
  * Creates a copy of the current matrix and multiplies and input
  *matrix by the copy. The new values are stored into the current
  *matrix giving a new pre multiplied net transform matrix
  */
void Matrix3f::preMultiply(const Matrix3f source)
{
    int row = 0;
    int x(0);
    int y(0);
    int z(0);
    int c(0);
    Matrix3f mine = Matrix3f(*this);
    while(row < mySize)
    {
        x = source.getElement(row, 0)*mine.getElement(0, 0)
                + source.getElement(row, 1)*mine.getElement(1, 0)
                + source.getElement(row, 2)*mine.getElement(2, 0)
                + source.getElement(row, 3)*mine.getElement(3, 0);
        y = source.getElement(row, 0)*mine.getElement(0, 1)
                + source.getElement(row, 1)*mine.getElement(1, 1)
                + source.getElement(row, 2)*mine.getElement(2, 1)
                + source.getElement(row, 3)*mine.getElement(3, 1);
        z = source.getElement(row, 0)*mine.getElement(0, 2)
                + source.getElement(row, 1)*mine.getElement(1, 2)
                + source.getElement(row, 2)*mine.getElement(2, 2)
                + source.getElement(row, 3)*mine.getElement(3, 2);
        c = source.getElement(row, 0)*mine.getElement(0, 2)
                + source.getElement(row, 1)*mine.getElement(1, 3)
                + source.getElement(row, 2)*mine.getElement(2, 3)
                + source.getElement(row, 3)*mine.getElement(3, 3);
        myMatrix[row][0] = x;
        myMatrix[row][1] = y;
        myMatrix[row][2] = z;
        myMatrix[row][3] = c;
        row++;
    }//while

}//preMultiply

/*
  * Multiplies the current net matrix by an input matrix.
  *The new values are stored into the current
  *matrix giving a new pre multiplied net transform matrix
  *Does not need a copy of the matrix because I do an entire row's
  *calculation before changing values. That row is never used again
  */
void Matrix3f::postMultiply(const Matrix3f source)
{
    int row = 0;
    float x(0);
    float y(0);
    float z(0);
    float c(0);
    while(row < mySize)
    {
        x = myMatrix[row][0]*source.getElement(0, 0)
                +myMatrix[row][1]*source.getElement(1, 0)
                +myMatrix[row][2]*source.getElement(2, 0)
                +myMatrix[row][3]*source.getElement(3, 0);
        y = myMatrix[row][0]*source.getElement(0, 1)
                +myMatrix[row][1]*source.getElement(1, 1)
                +myMatrix[row][2]*source.getElement(2, 1)
                +myMatrix[row][3]*source.getElement(3, 1);
        z = myMatrix[row][0]*source.getElement(0, 2)
                +myMatrix[row][1]*source.getElement(1, 2)
                +myMatrix[row][2]*source.getElement(2, 2)
                +myMatrix[row][3]*source.getElement(3, 2);
        c = myMatrix[row][0]*source.getElement(0, 3)
                +myMatrix[row][1]*source.getElement(1, 3)
                +myMatrix[row][2]*source.getElement(2, 3)
                +myMatrix[row][3]*source.getElement(3, 3);
        myMatrix[row][0] = x;
        myMatrix[row][1] = y;
        myMatrix[row][2] = z;
        myMatrix[row][3] = c;
        row++;
    }//while
    //print();
}//postMultiply

/*
  * Returns an element at a chosen row and column
  */
float Matrix3f::getElement(int row, int col) const
{
    float x = 0.0f;
    if( 0 <= row && 2>=row
            && 0 <= col && 2>= col)
        x = myMatrix[row][col];
    //cout << "Row: " << row << " Col: " << col << " Value: " << x << endl;
    //print();
    return x;}//getElement

void Matrix3f::setCell(int row, int col, float val)
{
    myMatrix[row][col] = val;
}
