#ifndef BYTE_H
#define BYTE_H
#include "binaryCode.h"
#define bool int

typedef struct{
    BC_Bit array[8];
} B_Byte;

/**
 * @brief B_Byte constructor
 * @param b1 first bit
 * @param b2 second bit
 * @param b3 third bit
 * @param b4 fourth bit
 * @param b5 fifth bit
 * @param b6 sixth bit
 * @param b7 seventh bit
 * @param b8 height bit
 * @return The constructed byte composed of the 8 bits
*/
B_Byte B_byte(BC_Bit b1, BC_Bit b2, BC_Bit b3, BC_Bit b4, BC_Bit b5, BC_Bit b6, BC_Bit b7, BC_Bit b8);

/**
 * @brief Returns the bit at position i
 * @param byte The byte you want to extract the bit from
 * @param i The position of the bit you want to extract
 * @return the bit at position i in the byte
*/
BC_Bit B_getBit(B_Byte byte, int i);

/**
 * @brief Sets the bit at position i to bit
 * @param byte The byte you want to set the bit in
 * @param i The position of the bit you want to set
 * @param bit The value of the bit you want to set
*/
void B_setBit(B_Byte* byte, int i, BC_Bit bit);

/**
 * @brief Converts a byte to a natural number
 * @param byte The byte you want to convert
 * @return The natural number corresponding to the byte
*/
unsigned int B_byteToNatural(B_Byte byte);

/**
 * @brief Checks for equality between two bytes
 * @param byte1 The first byte
 * @param byte2 The second byte
 * @return 1 if the bytes are equal, 0 otherwise
*/
bool B_equals(B_Byte byte1, B_Byte byte2);

B_Byte B_charToByte(char inputChar);
#endif
