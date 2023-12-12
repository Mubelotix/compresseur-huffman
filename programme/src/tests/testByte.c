#include <CUnit/Basic.h>
#include "byte.h"

int init_suite_success(void) { 
  return 0; 
}

int clean_suite_success(void) { 
  return 0; 
}

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

int main(int argc, char** argv){
  CU_pSuite pSuite = NULL;

  /* initialisation du registre de tests */
  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  /* ajout d'une suite de test */
  pSuite = CU_add_suite("Tests boite noire : byte", init_suite_success, clean_suite_success);
  if (NULL == pSuite) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* Ajout des tests à la suite de tests boite noire */
  if ((NULL == CU_add_test(pSuite, "Test get bit", test_getBit))
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