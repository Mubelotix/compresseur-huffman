#include "priorityQueue.h"
#include "huffmanTree.h"
#include <stdio.h>
#include <errno.h>

PQ_PriorityQueue PQ_new() {
    PQ_PriorityQueue result;
    result.length = 0;
    return result;
}

PQ_PriorityQueue PQ_fromStatistics(S_Statistics stats) {
    PQ_PriorityQueue result = PQ_new();
    for (int i = 0; i < S_MAX; i++) {
        B_Byte byte = B_fromNatural(i);
        if (S_getCount(stats, byte) > 0) {
            HT_HuffmanTree ht = HT_createLeaf(S_getCount(stats, byte), B_fromNatural(i));
            PQ_insertTree(&result, ht);
        }
    }
    return result;
}

unsigned int PQ_length(PQ_PriorityQueue queue) {
    return queue.length;
}

int PQ_getInsertionIndex(PQ_PriorityQueue *queue, HT_HuffmanTree ht) {
    // TODO: having binary search here would be nice
    int i = 0;
    while (i < queue->length && HT_getOccurence(queue->elements[i]) > HT_getOccurence(ht)) {
        i++;
    }
    return i;
}

void PQ_shiftRight(PQ_PriorityQueue *queue, int index) {
    if (queue->length == MAX) {
        errno = EOVERFLOW;
        return;
    }
    int i = queue->length;
    queue->length++;
    while (i > index) {
        queue->elements[i] = queue->elements[i - 1];
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
    if (queue->length <= 0) {
        errno = ENOENT;
        return NULL;
    }
    queue->length--;
    return queue->elements[queue->length];
}

HT_HuffmanTree PQ_intoHuffmanTree(PQ_PriorityQueue priority_queue) {
    while (PQ_length(priority_queue) > 1) {
        HT_HuffmanTree leftChild = PQ_popTree(&priority_queue);
        HT_HuffmanTree rightChild = PQ_popTree(&priority_queue);
        HT_HuffmanTree node = HT_createNode(leftChild, rightChild);
        PQ_insertTree(&priority_queue, node);
    }
    return PQ_popTree(&priority_queue);
}

void PQ_debug(PQ_PriorityQueue queue) {
    printf("Priority queue:\n");
    for (int i = 0; i < queue.length; i++) {
        if (HT_isALeaf(queue.elements[i])) {
            printf("\t%d: %d\n", B_byteToNatural(HT_getByte(queue.elements[i])), HT_getOccurence(queue.elements[i]));
        } else {
            printf("\t%d\n", HT_getOccurence(queue.elements[i]));
        }
    }
    printf("\tLength: %d\n", queue.length);
}
