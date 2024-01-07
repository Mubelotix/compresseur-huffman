#include <CUnit/Basic.h>
#include "byte.h"

void B_testByteToNatural() {
    B_Byte byte = B_byte(1, 0, 1, 1, 0, 1, 0, 0);
    CU_ASSERT_EQUAL(B_byteToNatural(byte) , 180);
}

void B_testFromNaturel() {
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

CU_ErrorCode B_createByteTestSuite() {
    // Create the suite
    CU_pSuite pSuite = CU_add_suite("Tests boite noire : statistics", NULL, NULL);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Add the tests to the suite
    if ((NULL == CU_add_test(pSuite, "Test byteToNatural", B_testByteToNatural))
        || (NULL == CU_add_test(pSuite, "Test fromNatural", B_testFromNaturel))
        || (NULL == CU_add_test(pSuite, "Test equals", B_testEquals))
        ) 
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    return CUE_SUCCESS;
}