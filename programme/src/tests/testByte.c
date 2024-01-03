#include <CUnit/Basic.h>
#include "byte.h"

void test_getBit() {
    B_Byte byte = B_byte(1, 0, 1, 1, 0, 1, 0, 1);

    CU_ASSERT_EQUAL(B_getBit(byte, 0), 1);
    CU_ASSERT_EQUAL(B_getBit(byte, 1), 0);
    CU_ASSERT_EQUAL(B_getBit(byte, 2), 1);
    CU_ASSERT_EQUAL(B_getBit(byte, 3), 1);
    CU_ASSERT_EQUAL(B_getBit(byte, 4), 0);
    CU_ASSERT_EQUAL(B_getBit(byte, 5), 1);
    CU_ASSERT_EQUAL(B_getBit(byte, 6), 0);
    CU_ASSERT_EQUAL(B_getBit(byte, 7), 1);
}

void test_setBit() {
    B_Byte byte = B_byte(0, 0, 0, 0, 0, 0, 0, 0);

    B_setBit(&byte, 2, 1);
    CU_ASSERT_EQUAL(B_getBit(byte, 2), 1);

    B_setBit(&byte, 5, 1);
    CU_ASSERT_EQUAL(B_getBit(byte, 5), 1);

    B_setBit(&byte, 7, 1);
    CU_ASSERT_EQUAL(B_getBit(byte, 7), 1);

    CU_ASSERT_EQUAL(B_getBit(byte, 0), 0);
    CU_ASSERT_EQUAL(B_getBit(byte, 1), 0);
    CU_ASSERT_EQUAL(B_getBit(byte, 3), 0);
    CU_ASSERT_EQUAL(B_getBit(byte, 4), 0);
    CU_ASSERT_EQUAL(B_getBit(byte, 6), 0);
}

void test_byteToNatural() {
    B_Byte byte1 = B_byte(1, 0, 0, 0, 0, 0, 1, 1);
    B_Byte byte2 = B_byte(0, 1, 1, 1, 1, 1, 0, 0);

    CU_ASSERT_EQUAL(B_byteToNatural(byte1), 131);
    CU_ASSERT_EQUAL(B_byteToNatural(byte2), 28);
}

CU_ErrorCode B_createByteTestSuite() {
    // Create the suite
    CU_pSuite pSuite = CU_add_suite("Tests boite noire : byte", NULL, NULL);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Add the tests to the suite
    if ((NULL == CU_add_test(pSuite, "Test getBit", test_getBit))
        || (NULL == CU_add_test(pSuite, "Test setBit", test_setBit))
        || (NULL == CU_add_test(pSuite, "Test byteToNatural", test_byteToNatural))) 
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    return CUE_SUCCESS;
}
