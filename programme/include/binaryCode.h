#ifndef BINARYCODE_H
#define BINARYCODE_H
#define MAX 256  

typedef enum{0,1} Bit;

typedef struct{
    Bit bits[MAX];
    int length;
}BinaryCode;

BinaryCode BC_binaryCode();
void BC_addBit(BinaryCode* pbc, Bit b);
int BC_getLength(BinaryCode* pbc);
Bit BC_getBit(BinaryCode* pbc, int pos);
void BC_concatenate(BinaryCode* pbc1, BinaryCode* pbc2);

#endif
