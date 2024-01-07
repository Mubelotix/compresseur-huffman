#include <CUnit/CUnit.h>
#include "priorityQueue.h"
#include "huffmanTree.h"

//test axiome : length(newPriorityQueue()) = 0
void PQ_testNewPriorityQueue() {
    PQ_PriorityQueue queue = PQ_new();

    CU_ASSERT_EQUAL(queue.length , 0);
}

//test axiome : length(insertTree(q, ht)) = length(q) + 1
void PQ_testInsertTree() {
    PQ_PriorityQueue queue = PQ_new();
    int occurence = 42;
    HT_HuffmanTree ht = HT_createTree(HT_createLeaf(occurence));
    PQ_insertTree(&queue, ht);

    CU_ASSERT_EQUAL(PQ_length(queue) , 1);
}

//test axiome : length(popTree(q)) = length(q) − 1  &  popTree(insertTree(q, ht)) = ht
void PQ_testPopTree() {
    PQ_PriorityQueue queue = PQ_new();
    int occurence = 42;
    HT_HuffmanTree ht = HT_createTree(HT_createLeaf(occurence));
    PQ_insertTree(&queue, ht);
    HT_HuffmanTree pop_ht = PQ_popTree(&queue);

    CU_ASSERT_EQUAL(PQ_length(queue) , 0);
    CU_ASSERT_EQUAL(ht , pop_ht);
}

void PQ_testGetInsertionIndex(){
    PQ_PriorityQueue queue = PQ_new();
    HT_HuffmanTree ht1, ht2, ht3;
    ht1 = HT_createLeaf(1);
    ht2 = HT_createLeaf(5);
    ht3 = HT_createLeaf(3);

    PQ_insertTree(&queue, ht1);
    PQ_insertTree(&queue, ht2);
    int index = PQ_getInsertionIndex(&queue,ht3);

    CU_ASSERT_TRUE((index >= 0) && (index <= queue.length));
    CU_ASSERT_EQUAL(index , 1);
}

void test_PQ_shiftRight() {
    PQ_PriorityQueue queue = PQ_new();
    HT_HuffmanTree ht1, ht2, ht3;
    ht1 = HT_createLeaf(1);
    ht2 = HT_createLeaf(5);
    ht3 = HT_createLeaf(3);

    PQ_insertTree(&queue, ht1);
    PQ_insertTree(&queue, ht2);
    PQ_insertTree(&queue, ht3);

    unsigned int initLength = queue.length;
    HT_HuffmanTree initElements[MAX];
    for (unsigned int i = 0; i < queue.length; ++i) {
        initElements[i] = queue.elements[i];
    }

    int shiftIndex = 1;
    PQ_shiftRight(&queue, shiftIndex);

    CU_ASSERT_EQUAL(queue.length, initLength + 1);
    // Elements at the shift index and before are the same as before
    for (unsigned int i = 0; i <= shiftIndex; ++i) {
        CU_ASSERT_EQUAL(queue.elements[i], initElements[i]);
    }
    // Elements after the shift index have been shifted to the right
    for (unsigned int i = shiftIndex + 1; i < queue.length; ++i) {
        CU_ASSERT_EQUAL(queue.elements[i], initElements[i - 1]);
    }
}
