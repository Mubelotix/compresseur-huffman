#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "huffmanTree.h"

#define MAX 256

struct PriorityQueue {
    HuffmanTree elements[MAX];
    unsigned int length;
};

PriorityQueue newPriorityQueue();
int PQ_getInsertionIndex(PriorityQueue queue, HuffmanTree ht);
void PQ_shiftRight(PriorityQueue *queue, int index);
void PQ_insertTree(PriorityQueue *queue, HuffmanTree ht);
HuffmanTree PQ_popTree(PriorityQueue *queue);

#endif
