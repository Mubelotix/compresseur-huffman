#include "statistics.h"

S_Statistics S_statistics()
{
    S_Statistics stats;
    for (int i = 0; i < S_MAX; i++)
    {
        stats.element[i] = 0;
    }

    return stats;
}

bool S_isEmpty(S_Statistics stats)
{
    return S_length(stats) == 0;
}

bool S_contains(S_Statistics stats, B_Byte element)
{
    return S_getCount(stats, element) > 0;
}

int S_getCount(S_Statistics stats, B_Byte element)
{
    unsigned int index = B_byteToNatural(element);
    return stats.element[index];
}

void S_incCount(S_Statistics *stats, B_Byte element)
{
    stats->element[B_byteToNatural(element)]++;
}

unsigned int S_length(S_Statistics stats)
{
    unsigned int length = 0;
    for (int i = 0; i < S_MAX; i++)
    {
        if (stats.element[i] > 0)
        {
            length++;
        }
    }
    return length;
}

int S_getElement(S_Statistics stats, int pos)
{
    return stats.element[pos];
}
