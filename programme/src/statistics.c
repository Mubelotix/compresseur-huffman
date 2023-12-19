#include "statistics.h"

S_Statistics S_statistics()
{
    S_Statistics stats;
    stats.nbOfElements = 0;
    for (int i = 0; i < S_MAX; i++)
    {
        stats.element[i] = 0;
    }

    return stats;
}

bool S_isEmpty(S_Statistics stats)
{
    int i = 0;
    bool flag = 0;

    while (i < S_MAX && !flag)
    {
        if (stats.element[i] > 0)
        {
            flag = 1;
        }
        i++;
    }

    return flag;
}

bool S_contains(S_Statistics stats, B_Byte element)
{
    return S_getCount(stats, B_byteToNatural(element));
}

int S_getCount(S_Statistics stats, int element)
{
    return stats.element[element];
}

void S_incCount(S_Statistics *stats, B_Byte element)
{
    stats->element[B_byteToNatural(element)]++;
}

int S_length(S_Statistics *stats)
{
    return stats->nbOfElements;
}

int S_getElement(S_Statistics stats, int pos)
{
    return stats.element[pos];
}