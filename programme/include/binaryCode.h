#ifndef BINARYCODE_H
#define BINARYCODE_H
#define BC_MAX 256
#define ZERO 0
#define ONE 1
#define bool int
#include "byte.h"

typedef enum {
    BC_ZERO = ZERO,
    BC_ONE = ONE
} BC_Bit;

typedef struct{
    BC_Bit bits[BC_MAX];
    unsigned int length;
} BC_BinaryCode;

BC_BinaryCode BC_binaryCode();
void BC_addBit(BC_BinaryCode* pbc, BC_Bit b);
unsigned int BC_getLength(BC_BinaryCode bc);
BC_Bit BC_getBit(BC_BinaryCode bc, unsigned int pos);
void BC_concatenate(BC_BinaryCode* pbc1, BC_BinaryCode* pbc2);
bool BC_equals(BC_BinaryCode bc1, BC_BinaryCode bc2);
B_Byte BC_removeFirstByte(BC_BinaryCode* pbc);
void BC_appendByte(BC_BinaryCode* pbc, B_Byte byte);
BC_BinaryCode BC_prefix(BC_BinaryCode bc, unsigned int length);
BC_BinaryCode BC_suffix(BC_BinaryCode bc, unsigned int start);

void BC_debug(BC_BinaryCode bc);

#endif
