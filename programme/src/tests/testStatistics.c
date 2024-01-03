#include <CUnit/Basic.h>

#include "statistics.h"
#include "byte.h"

// Test de l'axiome: contains(statistics, element)
void S_testContains(void) {
    S_Statistics stats = S_statistics();
    B_Byte element = B_byte(0, 0, 0, 0, 0, 0, 0, 1);

    S_incCount(&stats, element);

    CU_ASSERT_TRUE(S_contains(stats, element));
}

// Test de l'axiome: isEmpty()
void S_testIsEmpty(void) {
    S_Statistics emptyStats = S_statistics();
    S_Statistics nonEmptyStats = S_statistics();
    S_incCount(&nonEmptyStats, B_byte(0, 0, 0, 0, 0, 0, 0, 1));

    CU_ASSERT_TRUE(S_isEmpty(emptyStats));     //doit retourner vrai
    CU_ASSERT_FALSE(S_isEmpty(nonEmptyStats));  // doit retourner faux
}

// Test de l'axiome: getCount(S_statistics, element) >= 0
void S_testGetCount(void) {
    S_Statistics stats = S_statistics();
    B_Byte b = B_byte(0, 0, 0, 0, 0, 0, 0, 1);
    CU_ASSERT_EQUAL(S_getCount(stats, b), 0);

    S_incCount(&stats, b);
    CU_ASSERT(S_getCount(stats, b) > 0);
}

// Test de l'axiome: getElementCount(S_statistics) = 0
void S_testGetElementCount(void) {
    S_Statistics stats = S_statistics();

    CU_ASSERT_EQUAL(S_length(stats), 0);
}

// Test de l'axiome: getElementCount(incCount(stats, el), el) = getElementCount(stats, el) + 1
void S_testIncCount(void) {
    S_Statistics stats = S_statistics();
    B_Byte b = B_byte(0, 0, 0, 0, 0, 0, 0, 1);

    int countBefore = S_length(stats);
    S_incCount(&stats, b);
    int countAfter = S_length(stats);

    CU_ASSERT_EQUAL(countAfter, countBefore + 1);
}

CU_ErrorCode S_createStatisticsTestSuite() {
    // Create the suite
    CU_pSuite pSuite = CU_add_suite("Tests boite noire : statistics", NULL, NULL);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Add the tests to the suite
    if ((NULL == CU_add_test(pSuite, "Test contains", S_testContains ))
        || (NULL == CU_add_test(pSuite, "Test getCount", S_testGetCount))
        || (NULL == CU_add_test(pSuite, "Test getElementCount", S_testGetElementCount)) 
        || (NULL == CU_add_test(pSuite, "Test incCount", S_testIncCount))
        || (NULL == CU_add_test(pSuite, "Test S_isEmpty", S_testIsEmpty))
        ) 
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    return CUE_SUCCESS;
}
