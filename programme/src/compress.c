#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "compress.h"
#include "huffmanTree.h"
#include "statistics.h"
#include "codingTable.h"
#include "binaryCode.h"
#include "priorityQueue.h"

#define CLI_GREEN "\033[1;32m"
#define CLI_NORMAL "\033[0m"

/// @brief Count the number of occurences of each byte in a file
S_Statistics C_computeStatistics(FILE *file) {
    S_Statistics stats = S_statistics();
    B_Byte byte;
    unsigned char inputChar;

    while (fread(&inputChar, 1, 1, file) == 1) {
        byte = B_fromNatural((unsigned int) inputChar);
        S_incCount(&stats, byte);
    }

    return stats;
}

/// @brief Write a single byte to a file
void writeByte(FILE *file, char byte) {
    size_t written = fwrite(&byte, sizeof(char), 1, file);
    if (written != 1) {
        errno = ENOENT;
    }
}

/// @brief Save statistics to a file. Those are stored as a sequence of VarInts.
void C_saveStatistics(S_Statistics stats, FILE *file) {
    for (int i = 0; i < S_MAX; i++) {
        // Write a VarInt
        unsigned int count = stats.element[i];
        unsigned int first_byte = (count >> 14) & 0x7F; // bits -21 to -14
        unsigned int second_byte = (count >> 7) & 0x7F; // bits -14 to -7
        unsigned int third_byte = count & 0x7F; // last 7 bits
        if (first_byte != 0) {
            first_byte += 0x80; // set first bit
            second_byte += 0x80; // set first bit
            writeByte(file, first_byte);
            writeByte(file, second_byte);
            writeByte(file, third_byte);
        } else if (second_byte != 0) {
            second_byte += 0x80; // set first bit
            writeByte(file, second_byte);
            writeByte(file, third_byte);
        } else {
            writeByte(file, third_byte);
        }
    }
}

/// @brief Compress the file on the fly
void C_streamCompress(FILE *sourceFile, FILE *outputFile, CT_CodingTable *codingTable, int verbosity) {
    unsigned char inputChar;
    BC_BinaryCode buffer = BC_binaryCode();
    fseek(sourceFile, 0, SEEK_SET);
    while (fread(&inputChar, 1, 1, sourceFile) == 1) {
        BC_BinaryCode newBits = CT_getBinaryCode(*codingTable, B_fromNatural(inputChar));
        if (verbosity >= 3)
            BC_debug(newBits);
        if (verbosity >= 3)
            printf(" ");
        BC_concatenate(&buffer, &newBits);

        while (BC_getLength(buffer) >= 8) {
            unsigned char codeNat = B_byteToNatural(BC_removeFirstByte(&buffer));
            size_t result = fwrite(&codeNat, sizeof(char), 1, outputFile);
            if (result != 1) {
                fprintf(stderr, "Erreur lors de l'écriture des données compressées\n");
                return;
            }
        }
    }

    // Add padding for last byte and save it
    if (BC_getLength(buffer) > 0) {
        while (BC_getLength(buffer) < 8) {
            BC_addBit(&buffer, 0);
        }
        B_Byte code = BC_removeFirstByte(&buffer);
        unsigned char codeNat = B_byteToNatural(code);
        size_t result = fwrite(&codeNat, sizeof(char), 1, outputFile);
        if (result != 1) {
            fprintf(stderr, "Erreur lors de l'écriture des données compressées\n");
            return;
        }
    }
}

int isFileEmpty(FILE *file) {
    if (file == NULL) {
        perror("Le pointeur vers le fichier est NULL");
        return -1;
    }

    long currentPosition = ftell(file);
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, currentPosition, SEEK_SET);

    if (size == 0) {
        return 1;
    } else {
        return 0;
    }
}

void C_compressFile(char *nameSourceFile, int verbosity) {
    if (verbosity >= 1)
        printf("Compression du fichier %s...\n", nameSourceFile);

    // Open files
    FILE *sourceFile = fopen(nameSourceFile, "rb");
    if (sourceFile == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier source.\n");
        exit(EXIT_FAILURE);
    }

    FILE *outputFile = fopen("temp.huff", "wb"); // fichier destination "temp.huff" (a modifier)
    if (outputFile == NULL) {
        fclose(sourceFile);
        fprintf(stderr, "Erreur lors de la création du fichier temporaire.\n");
        exit(EXIT_FAILURE);
    }
    
    // Count characters
    if (verbosity >= 2)
        printf("\nCounting characters...\n");
    S_Statistics stats = C_computeStatistics(sourceFile);
    if (verbosity >= 2)
        S_debug(stats);

    // Order characters by frequency
    if (verbosity >= 2)
        printf("\nBuilding priority queue...\n");
    PQ_PriorityQueue queue = PQ_fromStatistics(stats);
    if (verbosity >= 2)
        PQ_debug(queue);

    // Build Huffman tree
    if (verbosity >= 2)
        printf("\nBuilding Huffman tree...\n");
    HT_HuffmanTree huffmanTree = PQ_intoHuffmanTree(queue);
    if (verbosity >= 2)
        HT_debug(huffmanTree);

    // Build coding table
    if (verbosity >= 2)
        printf("\nBuilding coding table...\n");
    CT_CodingTable codingTable = CT_fromHuffmanTree(huffmanTree);
    if (verbosity >= 2)
        CT_debug(codingTable);

    // Write magic number
    char *id = "HUFFMAN";
    fwrite(id, sizeof(char), strlen(id), outputFile);

    // Save statistics
    if (verbosity >= 2)
        printf("\nWriting data...\n");
    C_saveStatistics(stats, outputFile);
    C_streamCompress(sourceFile, outputFile, &codingTable, verbosity);
    if (verbosity >= 1)
        printf("\n%sDone! ✅%s\n", CLI_GREEN, CLI_NORMAL);

    // Close files and free memory
    fclose(sourceFile);
    fclose(outputFile);
    HT_destroy(huffmanTree);
}
