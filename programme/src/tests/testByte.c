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
