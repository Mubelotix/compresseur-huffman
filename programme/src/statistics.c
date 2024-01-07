#include "statistics.h"
#include <errno.h>

/// Read a single byte from a file
char readByte(FILE* file) {
    char byte;
    size_t read = fread(&byte, sizeof(char), 1, file);

    // Vérifier si la lecture a réussi
    if (read != 1) {
        errno = ENOENT; // Erreur de lecture
    }

    return byte;
}

/// Write a single byte to a file
void writeByte(FILE* file, char byte) {
    size_t written = fwrite(&byte, sizeof(char), 1, file);

    // Vérifier si l'écriture a réussi
    if (written != 1) {
        errno = ENOENT; // Erreur d'écriture
    }
}

S_Statistics S_statistics() {
    S_Statistics stats;
    for (int i = 0; i < S_MAX; i++)
    {
        stats.element[i] = 0;
    }

    return stats;
}

S_Statistics S_restore(FILE* file) {
    S_Statistics stats;
    for (int i = 0; i < S_MAX; i++)
    {
        // Read a VarInt
        char first_byte = readByte(file);
        unsigned int count = first_byte & 0x7F;
        if (first_byte & 0x80) {
            char second_byte = readByte(file);
            count <<= 7;
            count += second_byte & 0x7F;
            if (second_byte & 0x80) {
                char third_byte = readByte(file);
                count <<= 7;
                count += third_byte & 0x7F;
            }
        }

        stats.element[i] = count;
    }

    return stats;
}

void S_save(S_Statistics stats, FILE* file) {
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
            writeByte(file, fist_byte);
            writeByte(file, second_byte);
            writeByte(file, third_byte);
        } else if (second_byte != 0) {
            second_byte += 0x80; // 0b10000000
            writeByte(file, second_byte);
            writeByte(file, third_byte);
        } else {
            writeByte(file, third_byte);
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
