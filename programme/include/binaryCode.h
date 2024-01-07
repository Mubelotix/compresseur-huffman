#ifndef BINARYCODE_H
#define BINARYCODE_H

#include "byte.h"

#define BC_MAX 8
#define ZERO 0
#define ONE 1

/**
 * @brief Represents a binary bit.
 */
typedef enum {
    BC_ZERO = ZERO, ///< Represents the value 0
    BC_ONE = ONE    ///< Represents the value 1
} BC_Bit;

/**
 * @brief Represents a binary code.
 */
typedef struct {
    BC_Bit bits[BC_MAX]; ///< Array of binary bits
    unsigned int length;  ///< Length of the binary code
} BC_BinaryCode;

/**
 * @brief Creates an empty binary code.
 * @return An empty binary code.
 */
BC_BinaryCode BC_binaryCode();

/**
 * @brief Adds a bit to the end of the binary code.
 * @param pbc Pointer to the binary code.
 * @param b The bit to add.
 */
void BC_addBit(BC_BinaryCode* pbc, BC_Bit b);

/**
 * @brief Gets the length of the binary code.
 * @param bc The binary code.
 * @return The length of the binary code.
 */
unsigned int BC_getLength(BC_BinaryCode bc);

/**
 * @brief Gets the bit at a specific position in the binary code.
 * @param bc The binary code.
 * @param pos The position of the bit.
 * @return The bit at the specified position.
 */
BC_Bit BC_getBit(BC_BinaryCode bc, unsigned int pos);

/**
 * @brief Concatenates two binary codes.
 * @param pbc1 Pointer to the first binary code.
 * @param pbc2 Pointer to the second binary code.
 */
void BC_concatenate(BC_BinaryCode* pbc1, BC_BinaryCode* pbc2);

/**
 * @brief Checks for equality between two binary codes.
 * @param bc1 The first binary code.
 * @param bc2 The second binary code.
 * @return 1 if the binary codes are equal, 0 otherwise.
 */
bool BC_equals(BC_BinaryCode bc1, BC_BinaryCode bc2);

/**
 * @brief Removes and returns the first byte from the binary code.
 * @param pbc Pointer to the binary code.
 * @return The first byte removed from the binary code.
 */
B_Byte BC_removeFirstByte(BC_BinaryCode* pbc);

/**
 * @brief Appends a byte to the end of the binary code.
 * @param pbc Pointer to the binary code.
 * @param byte The byte to append.
 */
void BC_appendByte(BC_BinaryCode* pbc, B_Byte byte);

/**
 * @brief Creates a binary code consisting of the prefix of the given length.
 * @param bc The original binary code.
 * @param length The length of the prefix.
 * @return The binary code consisting of the prefix.
 */
BC_BinaryCode BC_prefix(BC_BinaryCode bc, unsigned int length);

/**
 * @brief Creates a binary code consisting of the suffix starting from the given position.
 * @param bc The original binary code.
 * @param start The starting position of the suffix.
 * @return The binary code consisting of the suffix.
 */
BC_BinaryCode BC_suffix(BC_BinaryCode bc, unsigned int start);

/**
 * @brief Outputs the binary code for debugging purposes.
 * @param bc The binary code to debug.
 */
void BC_debug(BC_BinaryCode bc);

#endif
