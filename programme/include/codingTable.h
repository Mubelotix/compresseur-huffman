#ifndef CODING_TABLE_H
#define CODING_TABLE_H

#include "binaryCode.h"
#include "byte.h"

/// @brief The maximum number of bytes in a coding table.
#define MAX 256

/// @brief An association between a byte and its binary code.
typedef struct {
    unsigned char Byte;
    unsigned char BinaryCode;
} Coding;

/// @brief A table associating bytes and their binary codes.
typedef struct {
    Coding tab[MAX];
    unsigned int length;
} CodingTable;

/**
 * @brief Creates a new coding table.
 * @return A new coding table.
*/
CodingTable CT_new();

/**
 * @brief Checks if a coding table is empty.
 * @param table The coding table to check.
 * @return True if the coding table is empty, false otherwise.
*/
bool CT_isEmpty(CodingTable table);

/**
 * @brief Gets the length of a coding table.
 * @param table The coding table to get the length of.
 * @return The length of the coding table.
*/
unsigned int CT_length(CodingTable table);

/**
 * @brief Checks if a coding table contains a byte.
 * @param table The coding table to check.
 * @param byte The byte to check.
 * @return True if the coding table contains the byte, false otherwise.
*/
bool CT_contains(CodingTable table, B_Byte byte);

/**
 * @brief Adds a byte and its binary code to a coding table.
 * @param table The coding table to add the byte and its binary code to.
 * @param byte The byte to add.
 * @param code The binary code to add.
*/
void CT_add(CodingTable *table, B_Byte byte, BC_BinaryCode code);

/**
 * @brief Gets the binary code of a byte in a coding table.
 * @param table The coding table to get the binary code from.
 * @param byte The byte to get the binary code of.
 * @return The binary code of the byte.
*/
BC_BinaryCode CT_getBinaryCode(CodingTable table, B_Byte byte);

/**
 * @brief Gets the byte of a binary code in a coding table.
 * @param table The coding table to get the byte from.
 * @param code The binary code to get the byte of.
 * @return The byte of the binary code.
*/
B_Byte CT_getByte(CodingTable table, BC_BinaryCode code);

#endif
