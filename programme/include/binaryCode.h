#ifndef BINARYCODE_H
#define BINARYCODE_H
#define MAX 8  

typedef enum{0,1} BC_Bit;

typedef struct{
    Bit bits[MAX];
    int length;
}BC_BinaryCode;

BC_BinaryCode BC_binaryCode();
void BC_addBit(BC_BinaryCode* pbc, BC_Bit b);
int BC_getLength(BC_BinaryCode* pbc);
Bit BC_getBit(BC_BinaryCode* pbc, unsigned int pos);
void BC_concatenate(BC_BinaryCode* pbc1, BC_BinaryCode* pbc2);

#endif
