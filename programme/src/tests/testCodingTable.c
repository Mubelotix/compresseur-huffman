#include <CUnit/CUnit.h>
#include "codingTable.h"
#include "binaryCode.h"
#include "byte.h"

void CT_testContainsAndAdd() {
    CT_CodingTable table = CT_new();
    BC_Bit b0 = BC_ZERO;
    BC_Bit b1 = BC_ONE;
    BC_BinaryCode code = BC_binaryCode();
    BC_addBit(&code, b0);
    BC_addBit(&code, b1);
    BC_addBit(&code, b0);
    BC_addBit(&code, b1);
    B_Byte byte = B_byte(b0, b0, b1, b0, b1, b1, b1, b0);

    CU_ASSERT_TRUE(!CT_contains(table, byte));

    CT_add(&table, byte, code);

    CU_ASSERT_TRUE(CT_contains(table, byte));
}

void CT_testGetBinaryCode() {
    CT_CodingTable table = CT_new();
    BC_Bit b0 = BC_ZERO;
    BC_Bit b1 = BC_ONE;
    BC_BinaryCode code = BC_binaryCode();
    BC_addBit(&code, b0);
    BC_addBit(&code, b1);
    BC_addBit(&code, b0);
    BC_addBit(&code, b1);
    B_Byte byte = B_byte(b0, b0, b1, b0, b1, b1, b1, b0);

    CT_add(&table, byte, code);

    CU_ASSERT(BC_equals(CT_getBinaryCode(table, byte), code));
    //ne peut pas comparer deux BC faut comparer bit par bit
}

void CT_testGetByte() {
    CT_CodingTable table = CT_new();
    BC_Bit b0 = BC_ZERO;
    BC_Bit b1 = BC_ONE;
    BC_BinaryCode code = BC_binaryCode();
    BC_addBit(&code, b0);
    BC_addBit(&code, b1);
    BC_addBit(&code, b0);
    BC_addBit(&code, b1);
    B_Byte byte = B_byte(b0, b0, b1, b0, b1, b1, b1, b0);

    CT_add(&table, byte, code);

    CU_ASSERT(B_equals(CT_getByte(table, code), byte));
}

CU_ErrorCode CT_createCodingTableTestSuite() {

    CU_pSuite pSuite = CU_add_suite("Tests boite noire : coding table", NULL, NULL);
    if (pSuite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((CU_add_test(pSuite, "Test containsAndAdd", CT_testContainsAndAdd) == NULL) ||
        (CU_add_test(pSuite, "Test getBinaryCode", CT_testGetBinaryCode) == NULL) ||
        (CU_add_test(pSuite, "Test getByte", CT_testGetByte) == NULL)
        )
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    return CUE_SUCCESS;
}