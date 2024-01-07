#ifndef CODING_TABLE_H
#define CODING_TABLE_H

#include "binarycode.h"
#include "byte.h"
#include "huffmantree.h"
#include <stdio.h>

/**
 * @def MAX
 * @brief Number of combinations of 8 bits.
 */
#define MAX 256

/**
 * @def bool
 * @brief Redefinition of bool to int for compatibility.
 */
#define bool int

/**
 * @struct CT_OptionalBinaryCode
 * @brief An association between a byte and its binary code.
 */
typedef struct {
    bool present;              ///< Indicates if the binary code is present.
    BC_BinaryCode binary_code; ///< The binary code associated with the byte.
} CT_OptionalBinaryCode;

/**
 * @struct CT_CodingTable
 * @brief A table associating bytes and their binary codes.
 */
typedef struct {
    CT_OptionalBinaryCode tab[MAX]; ///< Array of optional binary codes.
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
bool CT_contains(CT_CodingTable table, B_Byte byte);

/**
 * @brief Adds a byte and its binary code to a coding table.
 * @param table The coding table to add the byte and its binary code to.
 * @param byte The byte to add.
 * @param code The binary code to add.
 * @exception EEXIST The byte is already in the coding table.
*/
void CT_add(CT_CodingTable* table, B_Byte byte, BC_BinaryCode code);

/**
 * @brief Gets the binary code of a byte in a coding table.
 * @param table The coding table to get the binary code from.
 * @param byte The byte to get the binary code of.
 * @return The binary code of the byte.
 * @exception ENOENT The byte is not in the coding table.
*/
BC_BinaryCode CT_getBinaryCode(CT_CodingTable table, B_Byte byte);

/**
 * @brief Gets the byte of a binary code in a coding table.
 * @param table The coding table to get the byte from.
 * @param code The binary code to get the byte of.
 * @return The byte of the binary code.
 * @exception ENOENT The binary code is not in the coding table.
*/
B_Byte CT_getByte(CT_CodingTable table, BC_BinaryCode code);

/**
 * @brief Creates a coding table from a Huffman tree.
 * @param tree The Huffman tree to create the coding table from.
 * @return The created coding table.
 */
CT_CodingTable CT_fromHuffmanTree(HT_HuffmanTree tree);

/**
 * @brief Outputs debugging information for the coding table.
 * @param table The coding table to debug.
 */
void CT_debug(CT_CodingTable table);

#endif
