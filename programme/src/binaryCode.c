#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "binaryCode.h"

BC_BinaryCode BC_binaryCode() {
    BC_BinaryCode bc;
    bc.length = 0;
    return bc;
}

void BC_addBit(BC_BinaryCode* pbc, BC_Bit b) {
    if (pbc->length < BC_MAX){
        pbc->bits[pbc->length] = b;
        pbc->length++;
    }
    else{
        printf("Error : BinaryCode length exceeds maximum allowed length. \n");
    }
}

unsigned int BC_getLength(BC_BinaryCode bc) {
    return bc.length;
}

BC_Bit BC_getBit(BC_BinaryCode bc, unsigned int pos) {
    assert(pos < bc.length);
    return bc.bits[pos];
}

void BC_concatenate(BC_BinaryCode* pbc1, BC_BinaryCode* pbc2) {
    unsigned int i;
    for (i=0; i < BC_getLength(*pbc2); i++) {
        BC_addBit(pbc1, BC_getBit(*pbc2,i));
    }
}

B_Byte BC_removeFirstByte(BC_BinaryCode* pbc) {
    if (BC_getLength(*pbc) < 8) {
        printf("Error : BinaryCode length is less than 8. \n");
        return B_byte(0, 0, 0, 0, 0, 0, 0, 0);
    }
    
    B_Byte res = B_byte(pbc->bits[0], pbc->bits[1], pbc->bits[2], pbc->bits[3], pbc->bits[4], pbc->bits[5], pbc->bits[6], pbc->bits[7]);

    for (unsigned int i=0; i < BC_getLength(*pbc)-8; i++) {
        pbc->bits[i] = pbc->bits[i+8];
    }
    pbc->length -= 8;

    return res;
}

void BC_appendByte(BC_BinaryCode* pbc, B_Byte byte) {
    unsigned char byteNat = B_byteToNatural(byte);
    for (unsigned int i=0; i < 8; i++) {
        BC_addBit(pbc, (byteNat >> (7-i)) & 1);
    }
}

BC_BinaryCode BC_prefix(BC_BinaryCode bc, unsigned int length) {
    BC_BinaryCode res = BC_binaryCode();
    for (unsigned int i=0; i < length; i++) {
        BC_addBit(&res, BC_getBit(bc, i));
    }
    return res;
}

BC_BinaryCode BC_suffix(BC_BinaryCode bc, unsigned int start) {
    BC_BinaryCode res = BC_binaryCode();
    for (unsigned int i=start; i < BC_getLength(bc); i++) {
        BC_addBit(&res, BC_getBit(bc, i));
    }
    return res;
}

bool BC_equals(BC_BinaryCode bc1, BC_BinaryCode bc2) {
    if (bc1.length != bc2.length) {
        return 0;
    } else {
        for (unsigned int i=0; i < bc1.length; i++){
            if (bc1.bits[i] != bc2.bits[i]){
                return 0;
            }
        }
        return 1;
    }
}

void BC_debug(BC_BinaryCode bc) {
    for (unsigned int i=0; i < bc.length; i++){
        printf("%d", bc.bits[i]);
    }
}
