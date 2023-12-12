#include <CUnit/CUnit.h>
#include "statistics.h"

// Test de l'axiome: contains(statistics, element)
void S_testContains(void) {
    Statistics stats = S_statistics();
    int element = 42;

    S_incCount(stats, element);

    CU_ASSERT_TRUE(S_contains(stats, element));
}

// // Test de l'axiome: isEmpty()
// void S_testIsEmpty(void) {
//     Statistics emptyStats = statistics();
//     Statistics nonEmptyStats = statistics();
//     incCount(nonEmptyStats, 42);  

//     CU_ASSERT_TRUE(isEmpty(emptyStats));     //doit retourner vrai
//     CU_ASSERT_FALSE(isEmpty(nonEmptyStats));  // doit retourner faux
// }

// // Test de l'axiome: getCount(statistics, element) >= 0
// void S_testGetCount(void) {
//     Statistics stats = statistics();
//     int element = 42;
//     statsInc = incCount(stats, element);

//     CU_ASSERT_TRUE(getCount(stats, element) = 0);
//     CU_ASSERT_TRUE(getCount(statsInc, element) > 0);
// }

// // Test de l'axiome: getElementCount(statistics) = 0
// void S_testGetElementCount(void) {
//     Statistics stats = statistics();

//     CU_ASSERT_TRUE(getElementCount(stats) = 0);
// }

// // Test de l'axiome: getElementCount(incCount(stats, el), el) = getElementCount(stats, el) + 1
// void S_testIncCount(void) {
//     Statistics stats = statistics();
//     int element = 42;

//     int countBefore = getElementCount(stats);
//     incCount(stats, element);
//     int countAfter = getElementCount(stats);

//     CU_ASSERT_EQUAL(countAfter, countBefore + 1);
// }


int main(int argc, char** argv){
  CU_pSuite pSuite = NULL;

  /* initialisation du registre de tests */
  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  /* ajout d'une suite de test */
  pSuite = CU_add_suite("Tests boite noire : statistics", init_suite_success, clean_suite_success);
  if (NULL == pSuite) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* Ajout des tests à la suite de tests boite noire */
  if ((NULL == CU_add_test(pSuite, "Test contains", S_testContains ))
    //   || (NULL == CU_add_test(pSuite, "Test getCount", S_testGetCount))
    //   || (NULL == CU_add_test(pSuite, "Test getElementCount", S_testGetElementCount)) 
    //   || (NULL == CU_add_test(pSuite, "Test incCount", S_testIncCount))
    //   || (NULL == CU_add_test(pSuite, "Test isEmpty", S_testIsEmpty))
      ) 
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

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
