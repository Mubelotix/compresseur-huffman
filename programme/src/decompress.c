#include "statistics.h"
#include "huffmanTree.h"
#include "binaryCode.h"
#include "priorityQueue.h"
#include <string.h>
#include <stddef.h>
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

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
    *statistics = S_deserialize(buffer);

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
            BC_Bit bit = B_getBit(sourceByte, bitReadPosition); 
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

}
