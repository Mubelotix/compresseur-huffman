#include "statistics.h"
#include "huffmanTree.h"
#include "binaryCode.h"
#include "priorityQueue.h"
#include "codingTable.h"
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
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

S_Statistics D_restoreStatistics(FILE* file) {
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

void D_writeData(FILE* sourceFile, FILE* outputFile, CT_CodingTable* codingTable, unsigned int expectedSize) {
    B_Byte byte;
    unsigned int byteNat;
    unsigned char inputChar;
    unsigned int currentSize = 0;

    if (expectedSize == 0) {
        return;
    }

    BC_BinaryCode unsavedBits = BC_binaryCode();
    while (fread(&inputChar, 1, 1, sourceFile) == 1) {
        byte = B_fromNatural(inputChar);
        BC_appendByte(&unsavedBits, byte);
        
        for (unsigned int length = 1; length <= BC_getLength(unsavedBits); length++) {
            BC_BinaryCode prefix = BC_prefix(unsavedBits, length);
            errno = 0;
            B_Byte byte = CT_getByte(*codingTable, prefix);
            if (errno == ENOENT) {
                continue;
            }
            unsavedBits = BC_suffix(unsavedBits, length);

            char c = B_byteToNatural(byte);


            BC_debug(prefix);
            printf(" ");
            size_t result = fwrite(&c, sizeof(char), 1, outputFile);
            if (result != 1) {
                fprintf(stderr, "Erreur lors de l'écriture des données decompressées\n");
                return;
            }
            currentSize++;
            if (currentSize == expectedSize) {
                return;
            }

            length = 1;
        }
    }
    
    printf("\n");
}

void D_decompressFile(char* nameSourceFile) {
    printf("Démpression du fichier %s...\n", nameSourceFile);

    // Open files
    FILE* sourceFile = fopen(nameSourceFile, "rb");
    if (sourceFile == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier source.\n");
        exit(EXIT_FAILURE);
    }

    FILE* outputFile = fopen("uncompressed.txt", "wb"); // fichier destination "temp.huff" (a modifier)
    if (outputFile == NULL) {
        fclose(sourceFile);
        fprintf(stderr, "Erreur lors de la création du fichier temporaire.\n");
        exit(EXIT_FAILURE);
    }

    // Read first 6 bytes
    char header[7];
    size_t read = fread(header, sizeof(char), 7, sourceFile);
    if (read != 7) {
        fprintf(stderr, "Erreur lors de la lecture de l'entête.\n");
        exit(EXIT_FAILURE);
    }
    if (strncmp(header, "HUFFMAN", 7) != 0) {
        fprintf(stderr, "L'entête du fichier n'est pas valide.\n");
        exit(EXIT_FAILURE);
    }

    // Read statistics
    printf("\nReading statistics...\n");
    S_Statistics stats = D_restoreStatistics(sourceFile);
    S_debug(stats);

    // Order characters by frequency
    printf("\nBuilding priority queue...\n");
    PQ_PriorityQueue queue = PQ_fromStatistics(stats);
    PQ_debug(queue);

    // Build Huffman tree
    printf("\nBuilding Huffman tree...\n");
    HT_HuffmanTree huffmanTree = PQ_intoHuffmanTree(queue);
    HT_debug(huffmanTree);

    // Build coding table
    printf("\nBuilding coding table...\n");
    CT_CodingTable codingTable = CT_fromHuffmanTree(huffmanTree);
    CT_debug(codingTable);

    printf("\nWriting data...\n");
    D_writeData(sourceFile, outputFile, &codingTable, S_length(stats));
}
