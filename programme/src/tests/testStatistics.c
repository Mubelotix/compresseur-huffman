#include <CUnit/Cunit.h>
#include "statistics.h"

// Test de l'axiome: contains(statistics, element)
void S_testContains(void) {
    Statistics stats = statistics();
    int element = 42;

    incCount(stats, element);

    CU_ASSERT_TRUE(contains(stats, element));
}

// Test de l'axiome: isEmpty(
void S_testIsEmpty(void) {
    Statistics emptyStats = statistics();
    Statistics nonEmptyStats = statistics();
    incCount(nonEmptyStats, 42);  

    CU_ASSERT_TRUE(isEmpty(emptyStats));     //doit retourner vrai
    CU_ASSERT_FALSE(isEmpty(nonEmptyStats));  // doit retourner faux
}

// Test de l'axiome: getCount(statistics, element) >= 0
void S_testGetCount(void) {
    Statistics stats = statistics();
    int element = 42;
    statsInc = incCount(stats, element);

    CU_ASSERT_TRUE(getCount(stats, element) = 0);
    CU_ASSERT_TRUE(getCount(statsInc, element) > 0);
}

// Test de l'axiome: getElementCount(statistics) = 0
void S_testGetElementCountAxiom(void) {
    Statistics stats = statistics();

    CU_ASSERT_TRUE(getElementCount(stats) = 0);
}

// Test de l'axiome: getElementCount(incCount(stats, el), el) = getElementCount(stats, el) + 1
void S_testIncCountAxiom(void) {
    Statistics stats = statistics();
    int element = 42;

    int countBefore = getElementCount(stats);
    incCount(stats, element);
    int countAfter = getElementCount(stats);

    CU_ASSERT_EQUAL(countAfter, countBefore + 1);
}