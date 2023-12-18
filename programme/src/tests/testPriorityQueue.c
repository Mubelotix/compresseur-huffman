#include <CUnit/CUnit.h>
#include "priorityQueue.h"
#include "huffmanTree.h"

//test axiome : lenght(newPriorityQueue()) = 0
void PQ_testNewPriorityQueue(void) {
    PQ_PriorityQueue queue = PQ_new();

    CU_ASSERT_TRUE(lenght(queue) = 0);
}

//test axiome : isEmpty(newPriorityQueue())
void PQ_testIsEmpty(void) {
    PQ_PriorityQueue queue = PQ_new();

    CU_ASSERT_TRUE(isEmpty(newPriorityQueue()));
}

//test axiome : lenght(insertTree(q, ht)) = lenght(q) + 1
void PQ_insertTree(void) {
    PQ_PriorityQueue queue = PQ_new();
    int occurence = 42;
    HT_HuffmanTree ht = HT_createTree(HT_createLeaf(occurence));
    PQ_insertTree(&queue, ht);

    CU_ASSERT_TRUE(lenght(queue) = 1);
}

//test axiome : lenght(popTree(q)) = lenght(q) − 1  &  popTree(insertTree(q, ht)) = ht
void PQ_testPopTree(void) {
    PQ_PriorityQueue queue = PQ_new();
    int occurence = 42;
    HT_HuffmanTree ht = HT_createTree(HT_createLeaf(occurence));
    PQ_insertTree(&queue, ht);
    HT_HuffmanTree pop_ht = PQ_popTree(&queue);

    CU_ASSERT_TRUE((lenght(queue) = 0) && (ht = pop_ht));
}
