#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "huffmanTree.h"

#define MAX 256

typedef struct {
    HT_HuffmanTree elements[MAX];
    unsigned int length;
} PQ_PriorityQueue;

PQ_PriorityQueue PQ_new();
int PQ_getInsertionIndex(PQ_PriorityQueue *queue, HT_HuffmanTree ht);
void PQ_shiftRight(PQ_PriorityQueue *queue, int index);
void PQ_insertTree(PQ_PriorityQueue *queue, HT_HuffmanTree ht);
HT_HuffmanTree PQ_popTree(PQ_PriorityQueue *queue);

#endif
