#ifndef BYTE_H
#define BYTE_H

/**
 * @def bool
 * @brief Redefinition of bool to int for compatibility.
 */
#define bool int

/**
 * @enum B_Bit
 * @brief Represents the two possible values of a bit: 0 or 1.
 */
typedef enum {
    B_ZERO = 0, ///< Represents the value 0.
    B_ONE = 1   ///< Represents the value 1.
} B_Bit;

/**
 * @struct B_Byte
 * @brief Represents a byte composed of 8 bits.
 */
typedef struct {
    unsigned char value; ///< The value of the byte.
} B_Byte;

/**
 * @brief Constructs a byte from 8 bits.
 * @param b1 First bit.
 * @param b2 Second bit.
 * @param b3 Third bit.
 * @param b4 Fourth bit.
 * @param b5 Fifth bit.
 * @param b6 Sixth bit.
 * @param b7 Seventh bit.
 * @param b8 Eighth bit.
 * @return The constructed byte composed of the 8 bits.
 */
B_Byte B_byte(B_Bit b1, B_Bit b2, B_Bit b3, B_Bit b4, B_Bit b5, B_Bit b6, B_Bit b7, B_Bit b8);

/**
 * @brief Converts a byte to a natural number.
 * @param byte The byte to convert.
 * @return The natural number corresponding to the byte.
 */
unsigned int B_byteToNatural(B_Byte byte);

/**
 * @brief Converts a natural number to a byte.
 * @param natural The natural number to convert.
 * @return The byte corresponding to the natural number.
 * @exception ERANGE if the natural number is greater than 255.
 */
B_Byte B_fromNatural(unsigned int natural);

/**
 * @brief Checks for equality between two bytes.
 * @param byte1 The first byte.
 * @param byte2 The second byte.
 * @return 1 if the bytes are equal, 0 otherwise.
 */
bool B_equals(B_Byte byte1, B_Byte byte2);

#endif
