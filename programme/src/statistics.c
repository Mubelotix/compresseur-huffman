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

S_Statistics S_deserialize(unsigned char* buffer) {
    S_Statistics stats;
    for (int i = 0; i < S_MAX; i++)
    {
        // Read a VarInt
        unsigned int count = buffer[0] & 0x7F;
        if (buffer[0] & 0x80) {
            count <<= 7;
            count += buffer[1] & 0x7F;
            if (buffer[1] & 0x80) {
                count <<= 7;
                count += buffer[2] & 0x7F;
                buffer += 1;
                // TODO: could go further
            }
            buffer += 1;
        }
        buffer += 1;

        stats.element[i] = count;
    }

    return stats;
}

void S_serialize(S_Statistics stats, unsigned char* buffer) {
    for (int i = 0; i < S_MAX; i++)
    {
        // Write a VarInt
        unsigned int count = stats.element[i];
        unsigned int fist_byte = count & (0x7F << 14); // 0b01111111
        unsigned int second_byte = count & (0x7F << 7); // 0b01111111
        unsigned int third_byte = count & 0x7F; // 0b01111111
        if (fist_byte != 0) {
            fist_byte += 0x80; // 0b10000000
            second_byte += 0x80; // 0b10000000
            buffer[0] = fist_byte;
            buffer[1] = second_byte;
            buffer[2] = third_byte;
            buffer += 3;
        } else if (second_byte != 0) {
            second_byte += 0x80; // 0b10000000
            buffer[0] = second_byte;
            buffer[1] = third_byte;
            buffer += 2;
        } else {
            buffer[0] = third_byte;
            buffer += 1;
        }
    }
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
