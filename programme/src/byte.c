#include <stdio.h>
#include "byte.h"

// Fonction B_byte
B_Byte B_byte(BC_Bit b1, BC_Bit b2, BC_Bit b3, BC_Bit b4, BC_Bit b5, BC_Bit b6, BC_Bit b7, BC_Bit b8) {
    B_Byte res;
    res.array[0] = b1;
    res.array[1] = b2;
    res.array[2] = b3;
    res.array[3] = b4;
    res.array[4] = b5;
    res.array[5] = b6;
    res.array[6] = b7;
    res.array[7] = b8;
    return res;
}

// Fonction B_getBit
BC_Bit B_getBit(B_Byte byte, int i) {
    // Précondition : i < 8
    return byte.array[i];
}

// Procédure setBit
void B_setBit(B_Byte* byte, int i, BC_Bit bit) {
    byte->array[i] = bit;
}

// Fonction B_byteToNatural
unsigned int B_byteToNatural(B_Byte byte) {
    unsigned int res = 0;
    for (int i = 0; i < 8; ++i) {
        res += byte.array[i] * (1 << (7 - i));
    }
    return res;
}

// Fonction B_equals
int B_equals(B_Byte byte1, B_Byte byte2) {
    for (int i = 0; i < 8; ++i) {
        if (byte1.array[i] != byte2.array[i]) {
            return 0;
        }
    }
    return 1;
}
