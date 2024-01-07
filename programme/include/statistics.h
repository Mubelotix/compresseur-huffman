#ifndef STATISTICS_H
#define STATISTICS_H

#include "byte.h"
#include <stdio.h>

#define S_MAX 256
#define bool int

/// @brief Structure holding for each byte its number of occurences.
typedef struct {
    unsigned int element[S_MAX];
} S_Statistics;

/**
 * @brief Creates an empty S_Statistics
 * @return an empty S_Statistics
 */
S_Statistics S_statistics();

/**
 * @brief Checks if all bytes have a count of 0
 * @param stats The statistics to check
 * @return true if stats is empty
 */
bool S_isEmpty(S_Statistics stats);

/**
 * @brief Checks that an element appears at least once in a document
 * @param stats The statistics for the document
 * @param element The element to check
 * @return true if stats contains element
 */
bool S_contains(S_Statistics stats, B_Byte byte);

/**
 * @brief Gets the number of occurences of an element in a document
 * @param stats The statistics for the document
 * @param element The element to check
 * @return the number of occurences of element in stats
 */
unsigned int S_getCount(S_Statistics stats, B_Byte byte);

/**
 * @brief Adds an occurence of an element to a document
 * @param stats The statistics for the document
 * @param element The element to add
 */
void S_incCount(S_Statistics *stats, B_Byte byte);

/**
 * @brief Gets the total number of bytes
 * @param stats The statistics for the document
 * @return the number of bytes
 */
unsigned int S_length(S_Statistics stats);

void S_debug(S_Statistics stats);

#endif
