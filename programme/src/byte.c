#include <stdio.h>
#include "byte.h"
#include <errno.h>

// Fonction B_byte
B_Byte B_byte(BC_Bit b1, BC_Bit b2, BC_Bit b3, BC_Bit b4, BC_Bit b5, BC_Bit b6, BC_Bit b7, BC_Bit b8) {
    if (b1 > 1 || b2 > 1 || b3 > 1 || b4 > 1 || b5 > 1 || b6 > 1 || b7 > 1 || b8 > 1) {
        errno = ERANGE;
        printf("B_byte: Error: bit value must be 0 or 1\n");
        return B_byte(0, 0, 0, 0, 0, 0, 0, 0);
    }
    B_Byte res;
    res.value = b1 << 8 | b2 << 7 | b3 << 6 | b4 << 5 | b5 << 4 | b6 << 3 | b7 << 2 | b8 << 1;
    return res;
}

// Fonction B_getBit
BC_Bit B_getBit(B_Byte byte, int i) {
    // Précondition : i < 8
    return byte.value >> i & 1;
}

// Procédure setBit
void B_setBit(B_Byte* byte, int i, BC_Bit bit) {
    if (bit > 1) {
        errno = ERANGE;
        printf("B_setBit: Error: bit value must be 0 or 1\n");
        return;
    }
    // Précondition : i < 8
    byte->value = byte->value & ~(1 << i) | bit << i;
}

// Fonction B_byteToNatural
unsigned int B_byteToNatural(B_Byte byte) {
    return (unsigned int) byte.value;
}

B_Byte B_fromNatural(unsigned int natural) {
    if (natural > 255) {
        errno = ERANGE;
        return B_byte(0, 0, 0, 0, 0, 0, 0, 0);
    }
    B_Byte res;
    res.value = (char) natural;
    return res;
}

// Fonction B_equals
bool B_equals(B_Byte byte1, B_Byte byte2) {
    return byte1.value == byte2.value;
}
