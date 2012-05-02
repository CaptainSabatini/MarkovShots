#include "bigTable.h"

bigTable::bigTable()
{
    for(int r(0); r < mySize; r++)
        for(int c(0); c < mySize; c++)
            myTable[r][c] = 0;
}

void bigTable::add(int row, int col)
{
    myTable[row][col]++;
}

int bigTable::getAt(int row, int col)
{
    return myTable[row][col];
}

float bigTable::rowSum(int row)
{
    float sum(0);
    for(int c(0); c < mySize; c++)
        sum += myTable[row][c];
    return sum;
}

float bigTable::getMarkov(int row, int col)
{
    float sum = rowSum(row);
    float ratio(0);
    if(sum)
     ratio = (float)(myTable[row][col]/sum);
    return ratio;
}
