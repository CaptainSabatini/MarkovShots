#ifndef SMALLTABLE_H
#define SMALLTABLE_H

#include <sstream>

class smallTable
{

private:

    enum {mySize = 6};
    int myTable[mySize][mySize];
    float rowSum(int row);

public:
    smallTable();
    void add(int row, int col);
    int getAt(int row, int col);
    float getMarkov(int row, int col);
};

#endif // SMALLTABLE_H
