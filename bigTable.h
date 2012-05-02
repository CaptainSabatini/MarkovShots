#ifndef BIGTABLE_H
#define BIGTABLE_H

#include <sstream>

class bigTable
{
private:
    enum {mySize = 9};
    int myTable[mySize][mySize];
    float rowSum(int row);

public:
    bigTable();
    void add(int row, int col);
    int getAt(int row, int col);
    float getMarkov(int row, int col);
};

#endif // BIGTABLE_H
