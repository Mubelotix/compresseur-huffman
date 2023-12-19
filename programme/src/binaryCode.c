#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "binaryCode.h"

BC_BinaryCode BC_binaryCode(){
    BC_BinaryCode bc;
    bc.length = 0;
    return bc;
}

void BC_addBit(BC_BinaryCode* pbc, BC_Bit b){
    if (pbc->length < BC_MAX){
        pbc->bits[pbc->length] = b;
        pbc->length++;
    }
    else{
        printf("Error : BinaryCode length exceeds maximum allowed length. \n");
    }
}

unsigned int BC_getLength(BC_BinaryCode bc){
    return bc.length;
}

BC_Bit BC_getBit(BC_BinaryCode bc, unsigned int pos){
    assert(pos < bc.length);
    return bc.bits[pos];
}

void BC_concatenate(BC_BinaryCode* pbc1, BC_BinaryCode* pbc2){
    unsigned int i;
    for (i=0; i < BC_getLength(*pbc2); i++){
        BC_addBit(pbc1, BC_getBit(*pbc2,i));
    }
}