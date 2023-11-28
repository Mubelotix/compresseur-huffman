#ifndef  __BINARYCODE__
#define __BINARYCODE__

typedef enumerate

BinaryCode binaryCode();
void addBit(BinaryCode* bc, Bit b);
int getLength(BinaryCode bc);
Bit getBit(BinaryCode bc, int pos);
void concatenate(BinaryCode* bc1, BinaryCode bc2);

#endif