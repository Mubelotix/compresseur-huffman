#ifndef BINARYCODE_H
#define BINARYCODE_H
#define MAX 8
#define ZERO 0
#define ONE 1

typedef enum {
    BC_ZERO = ZERO,
    BC_ONE = ONE
} BC_Bit;

typedef struct{
    BC_Bit bits[MAX];
    unsigned int length;
}BC_BinaryCode;

BC_BinaryCode* BC_binaryCode();
void BC_addBit(BC_BinaryCode* pbc, BC_Bit b);
unsigned int BC_getLength(BC_BinaryCode* pbc);
BC_Bit BC_getBit(BC_BinaryCode* pbc, unsigned int pos);
void BC_concatenate(BC_BinaryCode* pbc1, BC_BinaryCode* pbc2);

#endif
