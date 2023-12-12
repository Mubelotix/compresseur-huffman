#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "huffmanTree.h"

/// @brief Maximum number of huffman trees in the priority queue
#define MAX 256

/// @brief Priority queue of huffman trees.
typedef struct {
    HT_HuffmanTree elements[MAX];
    unsigned int length;
} PQ_PriorityQueue;

/** 
 * @brief Creates a brand new, empty priority queue.
 * @return A new priority queue.
 */
PQ_PriorityQueue PQ_new();

/** 
 * @brief Gets the index where the given huffman tree should be inserted.
 * @param queue The priority queue.
 * @param ht The huffman tree about to be inserted.
 * @return The index where the given huffman tree should be inserted.
 */
int PQ_getInsertionIndex(PQ_PriorityQueue *queue, HT_HuffmanTree ht);

/** 
 * @brief Shifts all elements from the given index to the right.
 * @param queue The priority queue.
 * @param index The index where the shift should start.
 */
void PQ_shiftRight(PQ_PriorityQueue *queue, int index);

/** 
 * @brief Inserts the given huffman tree into the priority queue.
 * @param queue The priority queue.
 * @param ht The huffman tree to insert.
 */
void PQ_insertTree(PQ_PriorityQueue *queue, HT_HuffmanTree ht);

/** 
 * @brief Pops the last element of the priority queue.
 * @param queue The priority queue.
 * @return The last element of the priority queue.
 */
HT_HuffmanTree PQ_popTree(PQ_PriorityQueue *queue);

#endif
