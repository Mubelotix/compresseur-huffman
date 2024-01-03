#include <CUnit/Basic.h>
#include "testStatistics.c"

// Compile by hand:
// gcc -c src/tests/runner.c src/statistics.c src/byte.c -I include && gcc -o testrunner runner.o statistics.o byte.o -lcunit
// TODO remove lines above

// Better approach
// gcc -c src/byte.c src/statistics.c src/tests/runner.c -I include
// ar rcs libhuffman.a statistics.o byte.o
// gcc -o runner runner.o -L. -lhuffman -lcunit

int main(int argc, char** argv) {
    S_createTestSuite();

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
