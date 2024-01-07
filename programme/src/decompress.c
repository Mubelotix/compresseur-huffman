#include "statistics.h"
#include "huffmanTree.h"
#include "binaryCode.h"
#include "priorityQueue.h"
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


typedef enum {
    DECOMPRESS_RESULT_OK,
    DECOMPRESS_RESULT_ERROR_FILE,
    DECOMPRESS_RESULT_ERROR_PREMATURE_END_OF_FILE,
    DECOMPRESS_RESULT_ERROR_INVALID_HEADER,
    DECOMPRESS_RESULT_ERROR_FAILED_TO_WRITE_OUTPUT_FILE,
    DECOMPRESS_RESULT_INCONSISTENT_DECOMPRESSED_FILE
} DecompressResult;

typedef uint64_t FileSize;

bool isFileCompressed(FILE *input)
{
    char identifier[4];
    if (fread(identifier, sizeof(char), sizeof(identifier), input) != 4)
        return false;

    if (strncmp(identifier, "HUFF", sizeof(identifier)) != 0)
        return false;

    return true;
}

DecompressResult readHeader(FILE *input, S_Statistics *statistics, FileSize *size)
{
    if (!isFileCompressed(input))
        return DECOMPRESS_RESULT_ERROR_INVALID_HEADER;
    if (fread(size, sizeof(FileSize), 1, input) != 1)
        return DECOMPRESS_RESULT_ERROR_INVALID_HEADER;
    unsigned char buffer[sizeof(statistics)];
    if (fread(buffer, sizeof(unsigned char), sizeof(buffer), input) != sizeof(buffer))
        return DECOMPRESS_RESULT_ERROR_INVALID_HEADER;
    *statistics = S_statistics(); // S_deserialize(buffer);

    return DECOMPRESS_RESULT_OK;
} 

DecompressResult decompressData(FILE *input, FILE *output, const HT_HuffmanTree tree, FileSize *decompressedSize)
{
    unsigned char bitReadPosition = 0;
    HT_HuffmanTree currentTree = tree;
    B_Byte sourceByte = B_byte(0,0,0,0,0,0,0,0);
    decompressedSize = 0;

    while (feof(input) == 0)
    {
        if (bitReadPosition > 7)
        {
            unsigned char bitsRead;
            if (fread(&bitsRead, sizeof(bitsRead), 1, input) != 1)
                return DECOMPRESS_RESULT_ERROR_PREMATURE_END_OF_FILE; 
            sourceByte = B_fromNatural(bitsRead);
            bitReadPosition = 0;
        }

        if (HT_isALeaf(currentTree))
        {                                                      
            BC_Bit bit = 0;// B_getBit(sourceByte, bitReadPosition); 
            if (bit == 0)
                currentTree = currentTree->leftChild;
            else
                currentTree = currentTree->rightChild;
            bitReadPosition++;
        }
        else
        {
            B_Byte destinationByte = HT_getByte(currentTree);          
            unsigned char naturalToWrite = B_byteToNatural(destinationByte);      
            if (fwrite(&naturalToWrite, sizeof(naturalToWrite), 1, output) != 1) 
                return DECOMPRESS_RESULT_ERROR_FAILED_TO_WRITE_OUTPUT_FILE;
            currentTree = tree; 
            *decompressedSize++;
        }
    }

    return DECOMPRESS_RESULT_OK;
}

DecompressResult decompress(FILE *input, FILE *output)
{
    assert(input != NULL);
    assert(output != NULL);

    if (ferror(input) || ferror(output))
        return DECOMPRESS_RESULT_ERROR_FILE;

    if (feof(input))
        return DECOMPRESS_RESULT_ERROR_PREMATURE_END_OF_FILE;

    DecompressResult result = DECOMPRESS_RESULT_OK;
    FileSize size;
    S_Statistics statistics;
    statistics = S_statistics();
    result = readHeader(input, &statistics, &size);

    if (result != DECOMPRESS_RESULT_OK)
        return result;

    PQ_PriorityQueue queue = PQ_fromStatistics(statistics);
    HT_HuffmanTree tree = PQ_intoHuffmanTree(queue);

    assert(tree != NULL);

    if (feof(input) != 0)
        return DECOMPRESS_RESULT_ERROR_PREMATURE_END_OF_FILE;

    result = decompressData(input, output, tree, &size);

    HT_destroy(tree);

    return result;
}

DecompressResult decompressErrorToString(DecompressResult error, char *buffer, FileSize buffer_size)
{
    switch (error)
    {
    case DECOMPRESS_RESULT_OK:
        strncpy(buffer, "No error", buffer_size);
        break;
    case DECOMPRESS_RESULT_ERROR_FILE:
        strncpy(buffer, "File error", buffer_size);
        break;
    case DECOMPRESS_RESULT_ERROR_PREMATURE_END_OF_FILE:
        strncpy(buffer, "Premature end of file", buffer_size);
        break;
    case DECOMPRESS_RESULT_ERROR_INVALID_HEADER:
        strncpy(buffer, "Invalid header", buffer_size);
        break;
    case DECOMPRESS_RESULT_ERROR_FAILED_TO_WRITE_OUTPUT_FILE:
        strncpy(buffer, "Failed to write output file", buffer_size);
        break;
    case DECOMPRESS_RESULT_INCONSISTENT_DECOMPRESSED_FILE:
        strncpy(buffer, "Inconsistent decompressed file", buffer_size);
        break;
    default:
        strncpy(buffer, "Unknown error", buffer_size);
        break;
    }
    return error;
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


}
