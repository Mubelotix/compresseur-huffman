#ifndef STATISTICS_H
#define STATISTICS_H

#include "byte.h"

#define S_MAX 256
#define bool int

/**
 * @brief S_Statistics
 * @param element : B_Byte
 * @param nbOfElements : int
 */
typedef struct
{
    int element[S_MAX];
    int nbOfElements;
} S_Statistics;

/**
 * @brief S_statistics constructor
 * @return S_Statistics
 */
S_Statistics S_statistics();

/**
 * @brief S_isEmpty
 * @param stats
 * @return true if stats is empty
 */
bool S_isEmpty(S_Statistics stats);

/**
 * @brief S_contains
 * @param stats : S_Statistics
 * @param element : B_Byte
 * @return true if stats contains element
 */
bool S_contains(S_Statistics stats, B_Byte element);

/**
 * @brief S_getCount
 * @param stats : S_Statistics
 * @param element : B_Byte
 * @return the number of occurences of element in stats
 */
int S_getCount(S_Statistics stats, B_Byte element);

/**
 * @brief S_incCount
 * @param stats : S_Statistics
 * @param element : B_Byte
 */
void S_incCount(S_Statistics *stats, B_Byte element);

/**
 * @brief S_length
 * @param stats : S_Statistics
 * @return the number of elements in stats
 */
int S_length(S_Statistics *stats);

/**
 * @brief S_getElement
 * @param stats : S_Statistics
 * @param pos : int
 * @return the element at position pos in stats
 */
int S_getElement(S_Statistics stats, int pos);

#endif
