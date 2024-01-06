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

bool S_contains(S_Statistics stats, unsigned int octet)
{
    return S_getCount(stats, octet) > 0;
}

unsigned int S_getCount(S_Statistics stats, unsigned int octet)
{
    return stats.element[octet];
}

void S_incCount(S_Statistics *stats, unsigned int octet)
{
    stats->element[octet]++;
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
