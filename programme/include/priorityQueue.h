#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "huffmantree.h"
#include "statistics.h"

/**
 * @brief Maximum number of Huffman trees in the priority queue.
 */
#define MAX 256

/**
 * @struct PQ_PriorityQueue
 * @brief Represents a priority queue of Huffman trees.
 */
typedef struct {
    HT_HuffmanTree elements[MAX];  ///< Array of Huffman trees.
    unsigned int length;           ///< Length of the priority queue.
} PQ_PriorityQueue;

/**
 * @brief Creates a brand new, empty priority queue.
 * @return A new priority queue.
 */
PQ_PriorityQueue PQ_new();

/**
 * @brief Creates a priority queue from statistics.
 * @param stats The statistics of the document.
 * @return A priority queue containing all the bytes of the document.
 */
PQ_PriorityQueue PQ_fromStatistics(S_Statistics stats);

/**
 * @brief Gets the length of the given priority queue.
 * @param queue The priority queue.
 * @return The length of the given priority queue.
 */
unsigned int PQ_length(PQ_PriorityQueue queue);

/**
 * @brief Gets the index where the given Huffman tree should be inserted.
 * @param queue The priority queue.
 * @param ht The Huffman tree about to be inserted.
 * @return The index where the given Huffman tree should be inserted.
 */
int PQ_getInsertionIndex(PQ_PriorityQueue *queue, HT_HuffmanTree ht);

/**
 * @brief Shifts all elements from the given index to the right.
 * @param queue The priority queue.
 * @param index The index where the shift should start.
 * @exception EOVERFLOW If the priority queue is full.
 */
void PQ_shiftRight(PQ_PriorityQueue *queue, int index);

/**
 * @brief Inserts the given Huffman tree into the priority queue.
 * @param queue The priority queue.
 * @param ht The Huffman tree to insert.
 * @exception EOVERFLOW If the priority queue is full.
 */
void PQ_insertTree(PQ_PriorityQueue *queue, HT_HuffmanTree ht);

/**
 * @brief Pops the last element of the priority queue.
 * @param queue The priority queue.
 * @return The last element of the priority queue.
 * @exception EOVERFLOW If the priority queue is empty.
 */
HT_HuffmanTree PQ_popTree(PQ_PriorityQueue *queue);

/**
 * @brief Builds a Huffman tree from the priority queue.
 * @param priority_queue The priority queue.
 * @return The Huffman tree.
 */
HT_HuffmanTree PQ_intoHuffmanTree(PQ_PriorityQueue priority_queue);

/**
 * @brief Outputs debugging information for the priority queue.
 * @param queue The priority queue to debug.
 */
void PQ_debug(PQ_PriorityQueue queue);

#endif
