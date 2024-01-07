#ifndef BYTE_H
#define BYTE_H
#define bool int

// TODO 
typedef enum {
    B_ZERO = 0,
    B_ONE = 1
} B_Bit;

typedef struct{
    unsigned char value;
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
B_Byte B_byte(B_Bit b1, B_Bit b2, B_Bit b3, B_Bit b4, B_Bit b5, B_Bit b6, B_Bit b7, B_Bit b8);

/**
 * @brief Converts a byte to a natural number
 * @param byte The byte you want to convert
 * @return The natural number corresponding to the byte
*/
unsigned int B_byteToNatural(B_Byte byte);

/**
 * @brief Converts a natural number to a byte
 * @param natural The natural number you want to convert
 * @return The byte corresponding to the natural number
 * @exception ERANGE if the natural number is greater than 255
*/
B_Byte B_fromNatural(unsigned int natural);

/**
 * @brief Checks for equality between two bytes
 * @param byte1 The first byte
 * @param byte2 The second byte
 * @return 1 if the bytes are equal, 0 otherwise
*/
bool B_equals(B_Byte byte1, B_Byte byte2);

#endif
