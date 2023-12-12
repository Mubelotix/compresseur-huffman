#include <CUnit/Basic.h>
#include "huffmanTree.h"
#include "byte.h"

void test_getRightChild() {
    // TO DO
}

void test_getLeftChild() {
    // TO DO
}

void test_getByte() {
    byte = B_byte(BC_Bit 0, BC_Bit 1, BC_Bit 1, BC_Bit 1, BC_Bit 0, BC_Bit 0, BC_Bit 0, BC_Bit 1)
    leaf = createLeaf(byte)
    CU_ASSERT_EQUAL(getByte(leaf), byte);
}

void test_createLeaf() {
    // TO DO
}

void test_newNode() {
    // TO DO
}

void test_destroy() {
    // TO DO
}

void test_createTree() {
    // TO DO
}

void test_isALeaf() {
    // TO DO
}

void test_getOccurence() {
    // TO DO
}

int main() {

    if (CU_initialize_registry() != CUE_SUCCESS) {
        return CU_get_error();
    }

    CU_pSuite suite = CU_add_suite("HuffmanTree_test", NULL, NULL);
    if (suite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((CU_add_test(suite, "test_createTree", test_createTree) == NULL) ||
        (CU_add_test(suite, "test_getRightChild", test_getRightChild) == NULL) ||
        (CU_add_test(suite, "test_getLeftChild", test_getLeftChild) == NULL) ||
        (CU_add_test(suite, "test_getByte", test_getByte) == NULL) ||
        (CU_add_test(suite, "test_createLeaf", test_createLeaf) == NULL)) ||
        (CU_add_test(suite, "test_newNode", test_newNode) == NULL)||
        (CU_add_test(suite, "test_destroy", test_destroy) == NULL)||
        (CU_add_test(suite, "test_getOccurence", test_getOccurence) == NULL)||
        (CU_add_test(suite, "test_isALeaf", test_isALeaf) == NULL){
        CU_cleanup_registry();
        return CU_get_error();
    }
    CU_basic_run_tests();

    CU_cleanup_registry();
    return CU_get_error();
}
