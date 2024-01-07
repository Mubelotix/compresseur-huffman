#include <CUnit/Basic.h>
#include "byte.h"

void B_test_byteToNatural() {
    B_Byte byte = B_byte(1, 0, 1, 1, 0, 1, 0, 0);
    CU_ASSERT_EQUAL(B_byteToNatural(byte) , 180);
}

void B_test_fromNaturel() {
    B_Byte byte = B_fromNatural(42);
    CU_ASSERT_EQUAL(B_byteToNatural(byte) , 42);
}

void B_testEquals() {
    //Comparaison de deux octets similaires
    B_Byte byte1 = B_byte(1, 0, 1, 1, 0, 1, 0, 0);
    B_Byte byte2 = B_byte(1, 0, 1, 1, 0, 1, 0, 0);
    CU_ASSERT_TRUE(B_equals(byte1, byte2));

    //Comparaison de deux octets différents
    B_Byte byte3 = B_byte(0, 1, 1, 1, 0, 1, 0, 0);
    CU_ASSERT_TRUE(!B_equals(byte1, byte3));
}