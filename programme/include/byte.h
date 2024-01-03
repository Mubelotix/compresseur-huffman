#ifndef BYTE_H
#define BYTE_H
#include "binaryCode.h"
#define bool int

typedef struct{
    BC_Bit array[8];
} B_Byte;

B_Byte B_byte(BC_Bit b1, BC_Bit b2, BC_Bit b3, BC_Bit b4, BC_Bit b5, BC_Bit b6, BC_Bit b7, BC_Bit b8);

BC_Bit B_getBit(B_Byte byte, unsigned int i);

void B_setBit(B_Byte* byte, unsigned int i, BC_Bit bit);

unsigned int B_byteToNatural(B_Byte byte);

bool B_equals(B_Byte byte1, B_Byte byte2);

#endif
