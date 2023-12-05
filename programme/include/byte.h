#ifndef BYTE_H
#define BYTE_H

typedef enum{0,1} Bit;

typedef struct{
    Bit array[8];
}Byte;

Byte B_byte(Bit b1, Bit b2, Bit b3, Bit b4, Bit b5, Bit b6, Bit b7, Bit b8);

Bit B_getBit(Byte byte, unsigned int i);

void B_setBit(Byte byte, unsigned int i, Bit bit);

unsigned int B_byteToNatural(Byte byte);

#endif