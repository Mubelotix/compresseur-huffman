#ifndef STATISTICS_H
#define STATISTICS_H

#include "byte.h"

#define MAX 256

/**
 * @brief S_Statictics
 * @param element : B_Byte
 * @param nbOfElements : int
*/
typedef struct{
    B_Byte element[MAX];
    int nbOfElements;
}S_Statictics;


/**
 * @brief S_statistics constructor
 * @return S_Statictics 
*/
S_Statictics S_statistics();

/**
 * @brief S_isEmpty
 * @param stats
 * @return true if stats is empty
*/
bool S_isEmpty(S_Statictics stats);

/**
 * @brief S_contains
 * @param stats : S_Statictics
 * @param element : B_Byte 
 * @return true if stats contains element
*/
bool S_contains(S_Statictics stats, B_Byte element);

/**
 * @brief S_getCount
 * @param stats : S_Statictics
 * @param element : B_Byte
 * @return the number of occurences of element in stats
*/
int S_getCount(S_Statictics stats, B_Byte element);

/**
 * @brief S_incCount
 * @param stats : S_Statictics
 * @param element : B_Byte
*/
void S_incCount(S_Statictics* stats, B_Byte element);

/**
 * @brief S_length
 * @param stats : S_Statictics
 * @return the number of elements in stats
*/
int S_length(S_Statictics* stats);

/**
 * @brief S_getElement
 * @param stats : S_Statictics
 * @param pos : int
 * @return the element at position pos in stats
*/
B_Byte S_getElement(S_Statictics stats, int pos);

#endif
