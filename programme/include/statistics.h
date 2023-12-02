#ifndef STATISTICS_H
#define STATISTICS_H

#define MAX 256

typedef struct{
    Byte element[MAX];
    int nbOfElements;
}S_Statictics;

S_Statictics S_statistics();

bool S_isEmpty(S_Statictics stats);

bool S_contains(S_Statictics stats, Byte element);

int S_getCount(S_Statictics stats, Byte element);

void S_incCount(S_Statictics* stats, Byte element);

int S_length(S_Statictics* stats);

Byte S_getElement(S_Statictics stats, int pos);

#endif // STATISTICS_H
