#include <stdio.h>
#include "byte.h"
#include <errno.h>

// Fonction B_byte
B_Byte B_byte(B_Bit b1, B_Bit b2, B_Bit b3, B_Bit b4, B_Bit b5, B_Bit b6, B_Bit b7, B_Bit b8) {
    if (b1 > 1 || b2 > 1 || b3 > 1 || b4 > 1 || b5 > 1 || b6 > 1 || b7 > 1 || b8 > 1) {
        errno = ERANGE;
        printf("B_byte: Error: bit value must be 0 or 1\n");
        return B_byte(0, 0, 0, 0, 0, 0, 0, 0);
    }
    B_Byte res;
    res.value = (b1 << 7) | (b2 << 6) | (b3 << 5) | (b4 << 4) | (b5 << 3) | (b6 << 2) | (b7 << 1) | b8;
    return res;
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
