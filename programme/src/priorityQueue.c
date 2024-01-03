#include "priorityQueue.h"
#include "huffmanTree.h"
#include <errno.h>

PQ_PriorityQueue PQ_new() {
    PQ_PriorityQueue result;
    result.length = 0;
    return result;
}

unsigned int PQ_lenght(PQ_PriorityQueue queue) {
    return queue.length;
}

int PQ_getInsertionIndex(PQ_PriorityQueue *queue, HT_HuffmanTree ht) {
    // TODO: having binary search here would be nice
    int i = 0;
    while (i < queue->length && HT_getOccurence(ht) > HT_getOccurence(queue->elements[i])) {
        i++;
    }
    return i;
}

void PQ_shiftRight(PQ_PriorityQueue *queue, int index) {
    if (queue->length == MAX) {
        errno = EOVERFLOW;
        return;
    }
    queue->length++;
    int i = queue->length;
    while (i > index) {
        queue->elements[i] = queue->elements[i-1];
        i--;
    }
}

void PQ_insertTree(PQ_PriorityQueue *queue, HT_HuffmanTree ht) {
    int i = PQ_getInsertionIndex(queue, ht);
    PQ_shiftRight(queue, i);
    if (errno == EOVERFLOW) {
        return;
    }
    queue->elements[i] = ht;
}

HT_HuffmanTree PQ_popTree(PQ_PriorityQueue *queue) {
    if (queue->length == 0) {
        errno = EOVERFLOW;
        return HT_new();
    }
    queue->length--;
    return queue->elements[queue->length];
}
