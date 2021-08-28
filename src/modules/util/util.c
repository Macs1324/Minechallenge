#ifndef __UTIL_C__

#define __UTIL_C__

#include "util.h"

int getBit(int n, int bit)
{
    (n & ( 1 << bit )) >> bit;
}

void setBit(int* n, int bit, int value)
{
    *n ^= (-value ^ *n) & (1UL << bit);
}

int getBits(int n, int startBit, int stopBit)
{
    int r = 0;
    for(int i = startBit; i < stopBit; i++)
    {
        setBit(&r, i, getBit(n, i));
    }

    return r;
}
void setBits(int* n, int startBit, int stopBit, int value)
{
    for(int i = startBit; i < stopBit; i++)
    {
        setBit(n, i, getBit(value, i));
    }
}

#endif