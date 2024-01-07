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

#define CLI_GREEN "\033[1;32m"
#define CLI_NORMAL "\033[0m"

/// @brief Read a single byte from a file
unsigned char readByte(FILE* file) {
    unsigned char byte;
    size_t read = fread(&byte, sizeof(char), 1, file);

    // Vérifier si la lecture a réussi
    if (read != 1) {
        errno = ENOENT; // Erreur de lecture
    }

    return byte;
}

/// @brief Reads statistics from a file. Those are stored as a sequence of VarInts.
S_Statistics D_restoreStatistics(FILE* file) {
    S_Statistics stats;
    for (int i = 0; i < S_MAX; i++) {
        // Read a VarInt
        unsigned char first_byte = readByte(file);
        unsigned int count = first_byte & 0x7F;
        if (first_byte & 0x80) {
            unsigned char second_byte = readByte(file);
            count <<= 7;
            count += second_byte & 0x7F;
            if (second_byte & 0x80) {
                unsigned char third_byte = readByte(file);
                count <<= 7;
                count += third_byte & 0x7F;
            }
        }

        stats.element[i] = count;
    }

    return stats;
}

/// @brief Decompress the file on the fly
void D_streamDecompress(FILE* sourceFile, FILE* outputFile, CT_CodingTable* codingTable, unsigned int expectedSize, int verbosity) {
    if (expectedSize == 0) {
        return;
    }

    unsigned char inputChar;
    unsigned int currentSize = 0;
    BC_BinaryCode buffer = BC_binaryCode();
    while (fread(&inputChar, 1, 1, sourceFile) == 1) {
        BC_appendByte(&buffer, B_fromNatural(inputChar));
        
        // Split the binary code into multiple candidates and test them
        for (unsigned int length = 1; length <= BC_getLength(buffer); length++) {
            BC_BinaryCode codeCandidate = BC_prefix(buffer, length);

            // Attempt to get the byte corresponding to the code candidate
            // If it succeeds, the candidate is valid
            errno = 0;
            B_Byte byte = CT_getByte(*codingTable, codeCandidate);
            if (errno == ENOENT) {
                continue;
            }

            // Remove the code from the buffer
            buffer = BC_suffix(buffer, length);

            // Log the code
            if (verbosity >= 3) BC_debug(codeCandidate);
            if (verbosity >= 3) printf(" ");

            // Write the byte to the output file
            char c = B_byteToNatural(byte);
            size_t result = fwrite(&c, sizeof(char), 1, outputFile);
            if (result != 1) {
                fprintf(stderr, "Erreur lors de l'écriture des données decompressées\n");
                return;
            }
            currentSize++;

            // Check if we have reached the end of the file (there is padding to ignore at the end)
            if (currentSize == expectedSize) {
                return;
            }

            // The buffer has been shortened, so we need to restart the loop
            length = 1;
        }
    }
}

void D_decompressFile(char* nameSourceFile, int verbosity) {
    if (verbosity >= 1) printf("Décompression du fichier %s...\n", nameSourceFile);

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
    if (verbosity >= 2) printf("\nReading statistics...\n");
    S_Statistics stats = D_restoreStatistics(sourceFile);
    if (verbosity >= 2) S_debug(stats);

    // Order characters by frequency
    if (verbosity >= 2) printf("\nBuilding priority queue...\n");
    PQ_PriorityQueue queue = PQ_fromStatistics(stats);
    if (verbosity >= 2) PQ_debug(queue);

    // Build Huffman tree
    if (verbosity >= 2) printf("\nBuilding Huffman tree...\n");
    HT_HuffmanTree huffmanTree = PQ_intoHuffmanTree(queue);
    if (verbosity >= 2) HT_debug(huffmanTree);

    // Build coding table
    if (verbosity >= 2) printf("\nBuilding coding table...\n");
    CT_CodingTable codingTable = CT_fromHuffmanTree(huffmanTree);
    if (verbosity >= 2) CT_debug(codingTable);

    if (verbosity >= 2) printf("\nWriting data...\n");
    D_streamDecompress(sourceFile, outputFile, &codingTable, S_length(stats), verbosity);
    if (verbosity >= 1) printf("\n%sDone! ✅%s\n", CLI_GREEN, CLI_NORMAL);

    // Close files and free memory
    fclose(sourceFile);
    fclose(outputFile);
    HT_destroy(huffmanTree);
}
