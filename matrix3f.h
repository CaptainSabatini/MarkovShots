#ifndef MATRIX3F_H
#define MATRIX3F_H
#include "Vector3f.h"
class Matrix3f
{
        private:
                enum {X=1, Y = 2, Z = 3, mySize = 4};
                float myMatrix[mySize][mySize];
        public:
                Matrix3f();
                Matrix3f(const Matrix3f& source);
                void identity();
                void setRow(const int row, const Vector3f source);
                void setCol(const int col, const Vector3f source);
                void translate(const float tx,  const float ty, const float tz);
                void scale(const float sx, const float sy, const float sz);
                void rotate(const float theta, int axis);
                void transformPoint(Vector3f& outPt, const Vector3f& inPt);
                void preMultiply(const Matrix3f source);
                void postMultiply(const Matrix3f source);
                float getElement(int row, int col) const;
                void setCell(int row, int col, float val);
};

#endif // MATRIX3F_H
