#include <CUnit/Basic.h>
#include "huffmanTree.h"
#include "byte.h"
// grosse galère grosse galère j'ai confondu noeud et arbre
void test_getRightChild() {
    B_Byte byte1 = B_byte(0,0,0,0,0,0,0,1);
    B_Byte byte2 = B_byte(0,0,0,0,0,0,1,0);
    HT_HuffmanTree ht = HT_createNode(HT_createLeaf(0,byte1), HT_createLeaf(0,byte2));
    HT_HuffmanTreeNode rc = HT_getRightChild(ht);
    CU_ASSERT_EQUAL(ht.rightChild, b);

    ht = HT_createNode(HT_createLeaf(0), HT_createLeaf(42));
    rc = HT_getRightChild(ht);
    CU_ASSERT_EQUAL(ht.rightChild, b);
}

void test_getLeftChild() {
    HT_HuffmanTreeNode ht = HT_createNode(HT_createLeaf(0), HT_createLeaf(0));
    HT_HuffmanTreeNode rc = HT_getLeftChild(ht);
    CU_ASSERT_EQUAL(ht.leftChild, b);

    ht = HT_createNode(HT_createLeaf(0), HT_createLeaf(42));
    rc = HT_getLeftChild(ht);
    CU_ASSERT_EQUAL(ht.leftChild, b);
}

void test_getByte() {
    Byte byte = B_byte( 0, 1, 1, 1, 0, 0, 0, 1);
    HT_HuffmanTreeNode leaf = HT_createLeaf(byte);
    CU_ASSERT_EQUAL(getByte(leaf), byte);

    byte = B_byte(1, 1, 1, 0, 0, 1, 1, 1);
    leaf = HT_createLeaf(byte);
    CU_ASSERT_EQUAL(getByte(leaf), byte);

    byte = B_byte(0, 0, 0, 0, 0, 0, 0, 0);
    leaf = HT_createLeaf(byte);
    CU_ASSERT_EQUAL(getByte(leaf), byte);

    byte = B_byte(1, 1, 1, 1, 1, 1, 1, 1);
    leaf = HT_createLeaf(byte);
    CU_ASSERT_EQUAL(getByte(leaf), byte);
}

void test_createLeaf() {
    HT_HuffmanTreeNode leaf = HT_createLeaf(0);
    CU_ASSERT_EQUAL(HT_getOccurence(leaf), 0);

    leaf = HT_createLeaf(42);
    CU_ASSERT_EQUAL(HT_getOccurence(leaf), 42);
}

void test_createTree() {
    HT_HuffmanTreeNode* ht = HT_createTree(HT_createNode(HT_createLeaf(0), HT_createLeaf(42)));
    CU_ASSERT_EQUAL(ht.occurence, HT_getOccurence(ht));
    CU_ASSERT_EQUAL(ht.leftChild, HT_getLeftChild(ht));
    CU_ASSERT_EQUAL(ht.rightChild, HT_getRightChild(ht));
}

void test_isALeaf() {
    HT_HuffmanTreeNode ht = HT_createNode(HT_createLeaf(0), HT_createLeaf(0));
    CU_ASSERT_EQUAL(HT_isALeaf(ht), 0);

    ht = HT_createLeaf(0);
    CU_ASSERT_EQUAL(HT_isALeaf(ht), 1);
}

void test_getOccurence() {
    HT_HuffmanTreeNode ht = HT_createNode(HT_createLeaf(42), HT_createLeaf(42));
    int res = 42 + 42;
    CU_ASSERT_EQUAL(res, HT_getOccurence(ht));
}

void test_createNode() {
    HT_HuffmanTreeNode leaf1 = HT_createLeaf(2);
    HT_HuffmanTreeNode leaf2 = HT_createLeaf(42);
    node = HT_createNode(leaf1, leaf2);
    CU_ASSERT_EQUAL(leaf1, HT_getLeftChild(node));
    CU_ASSERT_EQUAL(leaf2, HT_getLeftChild(node));
}

CU_ErrorCode HT_createHuffmanTreeTestSuite() {

    CU_pSuite pSuite = CU_add_suite("Tests boite noire : huffman tree", NULL, NULL);
    if (pSuite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((CU_add_test(pSuite, "Test createTree", test_createTree) == NULL) ||
        (CU_add_test(pSuite, "Test getRightChild", test_getRightChild) == NULL) ||
        (CU_add_test(pSuite, "Test getLeftChild", test_getLeftChild) == NULL) ||
        (CU_add_test(pSuite, "Test getByte", test_getByte) == NULL) ||
        (CU_add_test(pSuite, "Test createLeaf", test_createLeaf) == NULL)) ||
        (CU_add_test(pSuite, "Test createNode", test_createNode) == NULL)||
        (CU_add_test(pSuite, "Test getOccurence", test_getOccurence) == NULL)||
        (CU_add_test(pSuite, "Test isALeaf", test_isALeaf) == NULL)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    return CUE_SUCCESS;
}
