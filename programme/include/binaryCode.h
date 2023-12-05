#ifndef BINARYCODE_H
#define BINARYCODE_H
#define MAX=256  

typedef enum{0,1} Bit;

typedef struct{
    Bit bits[MAX];
    int length;
}BinaryCode;

BinaryCode BC_binaryCode();
void BC_addBit(BinaryCode* bc, Bit b);
int BC_getLength(BinaryCode bc);
Bit BC_getBit(BinaryCode bc, int pos);
void BC_concatenate(BinaryCode* bc1, BinaryCode bc2);

#endif
