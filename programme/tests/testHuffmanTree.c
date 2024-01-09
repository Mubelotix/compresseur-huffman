#include <CUnit/Basic.h>
#include "huffmanTree.h"
#include "byte.h"

void HT_testGetOccurrence() {
    B_Byte byte1 = B_byte(0,0,0,0,0,0,0,1);
    B_Byte byte2 = B_byte(0,0,0,0,0,0,1,0);
    HT_HuffmanTree leaf1 = HT_createLeaf(5, byte1);
    HT_HuffmanTree leaf2 = HT_createLeaf(3, byte2);
    HT_HuffmanTree node = HT_createNode(leaf1, leaf2);

    CU_ASSERT_EQUAL(HT_getOccurence(node), 8);

    HT_destroy(node);
}

void HT_testGetRightChild() {
    B_Byte byte1 = B_byte(0,0,0,0,0,0,0,1);
    B_Byte byte2 = B_byte(0,0,0,0,0,0,1,0);
    HT_HuffmanTree leaf1 = HT_createLeaf(5, byte1);
    HT_HuffmanTree leaf2 = HT_createLeaf(3, byte2);
    HT_HuffmanTree node = HT_createNode(leaf1, leaf2);

    HT_HuffmanTree rightChild = HT_getRightChild(node);
    CU_ASSERT_EQUAL(HT_getOccurence(rightChild), 3);

    HT_destroy(node);
}

void HT_testGetLeftChild() {
    B_Byte byte1 = B_byte(0,0,0,0,0,0,0,1);
    B_Byte byte2 = B_byte(0,0,0,0,0,0,1,0);
    HT_HuffmanTree leaf1 = HT_createLeaf(5, byte1);
    HT_HuffmanTree leaf2 = HT_createLeaf(3, byte2);
    HT_HuffmanTree node = HT_createNode(leaf1, leaf2);

    HT_HuffmanTree leftChild = HT_getLeftChild(node);
    CU_ASSERT_EQUAL(HT_getOccurence(leftChild), 5);

    HT_destroy(node);
}

void HT_testGetByte() {
    B_Byte byte = B_byte(0,0,0,0,0,0,0,1);
    HT_HuffmanTree leaf = HT_createLeaf(5, byte);

    CU_ASSERT_TRUE(B_equals(HT_getByte(leaf), byte));

    HT_destroy(leaf);
}

void HT_testIsALeaf() {
    B_Byte byte1 = B_byte(0,0,0,0,0,0,0,1);
    B_Byte byte2 = B_byte(0,0,0,0,0,0,1,0);
    
    HT_HuffmanTree leaf1 = HT_createLeaf(5, byte1);
    HT_HuffmanTree leaf2 = HT_createLeaf(3, byte2);

    HT_HuffmanTree node = HT_createNode(leaf1, leaf2);

    CU_ASSERT_TRUE(HT_isALeaf(leaf1));

    CU_ASSERT_TRUE(!HT_isALeaf(node));

    HT_destroy(node);
}


CU_ErrorCode HT_createHuffmanTreeTestSuite() {

    CU_pSuite pSuite = CU_add_suite("Tests boite noire : huffman tree", NULL, NULL);
    if (pSuite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((CU_add_test(pSuite, "Test getOccurence", HT_testGetOccurrence) == NULL) ||
        (CU_add_test(pSuite, "Test getRightChild", HT_testGetRightChild) == NULL) ||
        (CU_add_test(pSuite, "Test getLeftChild", HT_testGetLeftChild) == NULL) ||
        (CU_add_test(pSuite, "Test getByte", HT_testGetByte) == NULL) ||
        (CU_add_test(pSuite, "Test isALeaf", HT_testIsALeaf) == NULL)
        )
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    return CUE_SUCCESS;
}
