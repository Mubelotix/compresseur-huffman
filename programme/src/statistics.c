#include "statistics.h"
#include <errno.h>

S_Statistics S_statistics() {
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

bool S_contains(S_Statistics stats, B_Byte byte)
{
    if (B_byteToNatural(byte) >= S_MAX)
    {
        printf("Error: byte %d is out of range\n", B_byteToNatural(byte));
    }
    return S_getCount(stats, byte) > 0;
}

unsigned int S_getCount(S_Statistics stats, B_Byte byte)
{
    if (B_byteToNatural(byte) >= S_MAX)
    {
        printf("Error: byte %d is out of range\n", B_byteToNatural(byte));
    }
    return stats.element[B_byteToNatural(byte)];
}

void S_incCount(S_Statistics *stats, B_Byte byte)
{
    if (B_byteToNatural(byte) >= S_MAX)
    {
        printf("Error: byte %d is out of range\n", B_byteToNatural(byte));
    }
    stats->element[B_byteToNatural(byte)]++;
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

void S_debug(S_Statistics stats) {
    printf("Statistics:\n");
    unsigned long total = 0;
    for (int i = 0; i < 256; i++) {
        B_Byte byte = B_fromNatural(i);
        if (S_contains(stats, byte) && i != 10) {
            total += S_getCount(stats, byte);
            char associated_char = i;
            printf("\t%d: %d\n", associated_char, S_getCount(stats, byte));
        }
    }
    printf("\tTotal: %lu\n", total);
}
