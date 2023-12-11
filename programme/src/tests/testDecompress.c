#include <CUnit/Basic.h>
#include "decompress.h"

void test_decompress_with_empty_file() {
    FILE *file = fopen("test_decompress_with_empty_file", "w");
    
    CU_ASSERT_EQUAL(decompress(file), 0);
}

void test_decompress_with_one_byte() {
    // TODO
}

void test_decompress_with_only_same_byte() {
    // TODO
}

void test_decompress_with_another_type_of_file() {
    // TODO
}

void test_decompress_with_not_compressed_file() {
    // TODO
}

int main() {

    if (CU_initialize_registry() != CUE_SUCCESS) {
        return CU_get_error();
    }

    CU_pSuite suite = CU_add_suite("Decompress_test", NULL, NULL);
    if (suite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((CU_add_test(suite, "test_decompress_with_empty_file", test_decompress_with_empty_file) == NULL) ||
        (CU_add_test(suite, "test_decompress_with_one_byte", test_decompress_with_one_byte) == NULL) ||
        (CU_add_test(suite, "test_decompress_with_only_same_byte", test_decompress_with_only_same_byte) == NULL) ||
        (CU_add_test(suite, "test_decompress_with_another_type_of_file", test_decompress_with_another_type_of_file) == NULL)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    printf("\n");
    CU_basic_show_failures(CU_get_failure_list());
    printf("\n\n");

    CU_cleanup_registry();
    return CU_get_error();
}