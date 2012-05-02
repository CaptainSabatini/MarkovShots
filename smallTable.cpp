#include "smallTable.h"

smallTable::smallTable()
{
    for(int r(0); r < mySize; r++)
        for(int c(0); c < mySize; c++)
            myTable[r][c] = 0;
}

void smallTable::add(int row, int col)
{
    myTable[row][col]++;
}

int smallTable::getAt(int row, int col)
{
    return myTable[row][col];
}

float smallTable::rowSum(int row)
{
    float sum(0);
    for(int c(0); c < mySize; c++)
        sum += myTable[row][c];
    return sum;
}

float smallTable::getMarkov(int row, int col)
{
    float sum = rowSum(row);
    float ratio(0);
    if(sum)
     ratio = (float)(myTable[row][col]/sum);
    return ratio;
}
