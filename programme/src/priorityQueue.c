#include "priorityQueue.h"

PQ_PriorityQueue PQ_new() {
    PQ_PriorityQueue result;
    result.length = 0;
    return result;
}

int PQ_getInsertionIndex(PQ_PriorityQueue *queue, HT_HuffmanTree ht) {
    int i = 0;
    while (i < queue->length && HT_getOccurence(ht) > HT_getOccurence(queue->elements[i])) {
        i++;
    }
    return i;
}

void PQ_shiftRight(PQ_PriorityQueue *queue, int index) {
    // Overflow handling with erno
    if (queue->length == MAX) {
        return;
    }
    queue->length++; // TODO handle overflow
    int i = queue->length;
    while (i > index) {
        queue->elements[i] = queue->elements[i-1];
        i--;
    }
}

void PQ_insertTree(PQ_PriorityQueue *queue, HT_HuffmanTree ht) {
    int i = PQ_getInsertionIndex(queue, ht);
    PQ_shiftRight(queue, i); // Handle error
    queue->elements[i] = ht;
}

HT_HuffmanTree PQ_popTree(PQ_PriorityQueue *queue) {
    queue->length--;
    return queue->elements[queue->length];
}
