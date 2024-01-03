#ifndef CODING_TABLE_H
#define CODING_TABLE_H

#include "binaryCode.h"
#include "byte.h"

/// @brief Number of combinations of 8 bits.
#define MAX 256
#define bool int

/// @brief An association between a byte and its binary code.
typedef struct {
    bool present;
    BC_BinaryCode binary_code;
} CT_OptionalBinaryCode;

/// @brief A table associating bytes and their binary codes.
typedef struct {
    CT_OptionalBinaryCode tab[MAX];
} CT_CodingTable;

/**
 * @brief Creates a new coding table.
 * @return A new coding table.
*/
CT_CodingTable CT_new();

/**
 * @brief Checks if a coding table is empty.
 * @param table The coding table to check.
 * @return True if the coding table is empty, false otherwise.
*/
bool CT_isEmpty(CT_CodingTable table);

/**
 * @brief Checks if a coding table contains a byte.
 * @param table The coding table to check.
 * @param byte The byte to check.
 * @return True if the coding table contains the byte, false otherwise.
*/
bool CT_contains(CT_CodingTable table, unsigned int byte);

/**
 * @brief Adds a byte and its binary code to a coding table.
 * @param table The coding table to add the byte and its binary code to.
 * @param byte The byte to add.
 * @param code The binary code to add.
 * @exception EEXIST The byte is already in the coding table.
*/
void CT_add(CT_CodingTable *table, unsigned int byte, BC_BinaryCode code);

/**
 * @brief Gets the binary code of a byte in a coding table.
 * @param table The coding table to get the binary code from.
 * @param byte The byte to get the binary code of.
 * @return The binary code of the byte.
 * @exception ENOENT The byte is not in the coding table.
*/
BC_BinaryCode CT_getBinaryCode(CT_CodingTable table, unsigned int byte);

/**
 * @brief Gets the byte of a binary code in a coding table.
 * @param table The coding table to get the byte from.
 * @param code The binary code to get the byte of.
 * @return The byte of the binary code.
 * @exception ENOENT The binary code is not in the coding table.
*/
B_Byte CT_getByte(CT_CodingTable table, BC_BinaryCode code);

#endif
