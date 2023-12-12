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
bool CT_contains(CodingTable table, Byte byte);
void CT_add(CodingTable *table, Byte byte, BinaryCode code);
BinaryCode CT_getBinaryCode(CodingTable table, Byte byte);
Byte CT_getByte(CodingTable table, BinaryCode code);

#endif
