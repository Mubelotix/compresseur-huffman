#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "binaryCode.h"

BC_BinaryCode* BC_binaryCode(){
    BC_BinaryCode* pbc;
    pbc->length = 0;
    return pbc;
}

void BC_addBit(BC_BinaryCode* pbc, BC_Bit b){
    if (pbc->length < MAX){
        pbc->bits[pbc->length] = b;
        pbc->length++;
    }
    else{
        printf("Error : BinaryCode length exceeds maximum allowed length. \n");
    }
}

unsigned int BC_getLength(BC_BinaryCode* pbc){
    return pbc->length;
}

BC_Bit BC_getBit(BC_BinaryCode* pbc, unsigned int pos){
    assert(pos < pbc->length);
    return pbc->bits[pos];
}

void BC_concatenate(BC_BinaryCode* pbc1, BC_BinaryCode* pbc2){
    unsigned int i;
    for (i=0; i < BC_getLength(pbc2); i++){
        BC_addBit(pbc1, BC_getBit(pbc2,i));
    }
}