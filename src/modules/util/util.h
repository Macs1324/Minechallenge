#ifndef __UTIL_H__

#define __UTIL_H__

int getBit(int n, int bit);
void setBit(int* n, int bit, int value);

int getBits(int n, int startBit, int stopBit);
void setBits(int* n, int startBit, int stopBit, int value);

typedef struct
{
    int index;
    int generation;
}GenerationalIndex;

#endif