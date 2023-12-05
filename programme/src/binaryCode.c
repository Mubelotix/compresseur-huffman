#include <stdlib.h>
#include <stdio.h>
#include "binaryCode.h"

BinaryCode BC_binaryCode(){
    BinaryCode bc;
    bc.length = 0;
    return bc;
};

void BC_addBit(BinaryCode* bc, Bit b){

};

int BC_getLength(BinaryCode* bc){
    return bc.length;
};

Bit BC_getBit(BinaryCode* bc, int pos){

};

void BC_concatenate(BinaryCode* bc1, BinaryCode* bc2){

};

int main(){
    BinaryCode* pbc = BC_binaryCode();
    printf("longueur de %d", BC_getLength(pbc));
}