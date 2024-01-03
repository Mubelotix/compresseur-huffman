#include <CUnit/Basic.h>
#include "testStatistics.c"
#include "testByte.c"

int main(int argc, char** argv) {
    /* initialisation du registre de tests */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();
    
    // Initializing test suites
    // There should be one per test file, feel free to add your own
    // Do not forget to import the test file at the top of this file
    S_createStatisticsTestSuite();
    B_createByteTestSuite();

    /* Lancement des tests */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    printf("\n");
    CU_basic_show_failures(CU_get_failure_list());
    printf("\n\n");

    /* Nettoyage du registre */
    CU_cleanup_registry();
    return CU_get_error();
}
