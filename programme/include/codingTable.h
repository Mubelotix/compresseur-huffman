#ifndef CODING_TABLE_H
#define CODING_TABLE_H

#include "binaryCode.h"
#include "byte.h"

#define MAX 256

typedef struct {
    unsigned char Byte;
    unsigned char BinaryCode;
} Coding;

typedef struct {
    Coding tab[MAX];
    unsigned int length;
} CodingTable;

CodingTable CT_new();
bool CT_isEmpty(CodingTable table);
unsigned int CT_length(CodingTable table);
bool CT_contains(CodingTable table, B_Byte byte);
void CT_add(CodingTable *table, B_Byte byte, BC_BinaryCode code);
BC_BinaryCode CT_getBinaryCode(CodingTable table, B_Byte byte);
B_Byte CT_getByte(CodingTable table, BC_BinaryCode code);

#endif
