#ifndef STATISTICS_H
#define STATISTICS_H

#define MAX 256

/**
 * @brief S_Statictics
 * @param element : Byte
 * @param nbOfElements : int
*/
typedef struct{
    Byte element[MAX];
    int nbOfElements;
}Statictics;


/**
 * @brief S_statistics constructor
 * @return S_Statictics 
*/
Statictics S_statistics();

/**
 * @brief S_isEmpty
 * @param stats
 * @return true if stats is empty
*/
bool S_isEmpty(Statictics stats);

/**
 * @brief S_contains
 * @param stats : S_Statictics
 * @param element : Byte 
 * @return true if stats contains element
*/
bool S_contains(Statictics stats, Byte element);

/**
 * @brief S_getCount
 * @param stats : S_Statictics
 * @param element : Byte
 * @return the number of occurences of element in stats
*/
int S_getCount(S_Statictics stats, Byte element);

/**
 * @brief S_incCount
 * @param stats : S_Statictics
 * @param element : Byte
*/
void S_incCount(Statictics* stats, Byte element);

/**
 * @brief S_length
 * @param stats : S_Statictics
 * @return the number of elements in stats
*/
int S_length(Statictics* stats);

/**
 * @brief S_getElement
 * @param stats : S_Statictics
 * @param pos : int
 * @return the element at position pos in stats
*/
Byte S_getElement(Statictics stats, int pos);

#endif
