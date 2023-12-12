#include <CUnit/CUnit.h>
#include "priorityQueue.h"
#include "huffmanTree.h"

//test axiome : lenght(newPriorityQueue()) = 0
void S_testNewPriorityQueue(void) {
    PQ_PriorityQueue queue = newPriorityQueue();

    CU_ASSERT_TRUE(lenght(queue) = 0);
}

//test axiome : isEmpty(newPriorityQueue())
void S_testIsEmpty(void) {
    PQ_PriorityQueue queue = newPriorityQueue();

    CU_ASSERT_TRUE(isEmpty(newPriorityQueue()));
}

//test axiome : lenght(insertTree(q, ht)) = lenght(q) + 1
void S_testPopTree(void) {
    PQ_PriorityQueue queue = newPriorityQueue();
    int occurence = 42;
    HT_HuffmanTree ht = HT_createTree(HT_createLeaf(occurence));
    insertTree(queue, ht);

    CU_ASSERT_TRUE(lenght(queue) = 1);
}

//test axiome : lenght(popTree(q)) = lenght(q) − 1
void S_testPopTree(void) {
    PQ_PriorityQueue queue = newPriorityQueue();
    int occurence = 42;
    HT_HuffmanTree ht = HT_createTree(HT_createLeaf(occurence));
    insertTree(queue, ht);
    ht = popTree(queue);

    CU_ASSERT_TRUE(lenght(queue) = 0);
}

//test axiome : popTree(insertTree(q, ht)) = ht
void S_testPopTree(void) {
    PQ_PriorityQueue queue = newPriorityQueue();
    int occurence = 42;
    HT_HuffmanTree ht = HT_createTree(HT_createLeaf(occurence));
    insertTree(queue, ht);

    CU_ASSERT_TRUE(popTree(queue) = ht);
}
