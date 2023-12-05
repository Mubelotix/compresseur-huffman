#ifndef BYTE_H
#define BYTE_H

typedef enum{0,1} Bit_Bit;

typedef struct{
    Bit_Bit array[8];
}B_Byte;

B_Byte B_byte(Bit_Bit b1, Bit_Bit b2, Bit_Bit b3, Bit_Bit b4, Bit_Bit b5, Bit_Bit b6, Bit_Bit b7, Bit_Bit b8);

Bit_Bit B_getBit(B_Byte byte, unsigned int i);

void B_setBit(B_Byte* byte, unsigned int i, Bit_Bit bit);

unsigned int B_byteToNatural(B_Byte byte);

#endif