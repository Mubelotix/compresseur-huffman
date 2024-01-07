#ifndef STATISTICS_H
#define STATISTICS_H

#include "byte.h"
#include <stdio.h>

/**
 * @def S_MAX
 * @brief Maximum number of possible byte values.
 */
#define S_MAX 256

/**
 * @def bool
 * @brief Redefinition of bool to int for compatibility.
 */
#define bool int

/**
 * @struct S_Statistics
 * @brief Represents a structure holding, for each byte, its number of occurrences in a document.
 */
typedef struct {
    unsigned int element[S_MAX]; ///< Array holding the number of occurrences for each byte.
} S_Statistics;

/**
 * @brief Creates an empty S_Statistics.
 * @return An empty S_Statistics.
 */
S_Statistics S_statistics();

/**
 * @brief Checks if a byte appears at least once in a document.
 * @param stats The statistics for the document.
 * @param byte The byte to check.
 * @return true if stats contains the byte.
 */
bool S_contains(S_Statistics stats, B_Byte byte);

/**
 * @brief Gets the number of occurrences of a byte in a document.
 * @param stats The statistics for the document.
 * @param byte The byte to check.
 * @return The number of occurrences of the byte in stats.
 */
unsigned int S_getCount(S_Statistics stats, B_Byte byte);

/**
 * @brief Adds an occurrence of a byte to the document's statistics.
 * @param stats The statistics for the document.
 * @param byte The byte to add.
 */
void S_incCount(S_Statistics *stats, B_Byte byte);

/**
 * @brief Gets the total number of bytes in the document.
 * @param stats The statistics for the document.
 * @return The total number of bytes.
 */
unsigned int S_length(S_Statistics stats);

/**
 * @brief Outputs debugging information for the statistics.
 * @param stats The statistics to debug.
 */
void S_debug(S_Statistics stats);

#endif

