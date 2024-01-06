#include "statistics.h"
#include "huffmanTree.h"
#include "binaryCode.h"
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

DecompressResult readHeader(FILE *input, Statistics *statistics, FileSize *size)
{
    if (!isFileCompressed(input))
        return DECOMPRESS_RESULT_ERROR_INVALID_HEADER;
    if (fread(size, sizeof(FileSize), 1, input) != 1)
        return DECOMPRESS_RESULT_ERROR_INVALID_HEADER;
    unsigned char buffer[sizeof(statistics)];
    if (fread(buffer, sizeof(unsigned char), sizeof(buffer), input) != sizeof(buffer))
        return DECOMPRESS_RESULT_ERROR_INVALID_HEADER;
    statistics_deserialize(statistics, buffer); // on a pas cette fonction (go voir ça en call Discord)

    return DECOMPRESS_RESULT_OK;
} 

DecompressResult decompressData(FILE *input, FILE *output, const HuffmanTree tree, FileSize *decompressedSize)
{
    unsigned char bitReadPosition = 0;
    HuffmanTree currentTree = tree;
    Byte sourceByte = B_byte(0);
    decompressedSize = 0;

    while (feof(input) == 0)
    {
        if (bitReadPosition > 7)
        {
            unsigned char bitsRead;
            if (fread(&bitsRead, sizeof(bitsRead), 1, input) != 1)
                return DECOMPRESS_RESULT_ERROR_PREMATURE_END_OF_FILE; 
            sourceByte = B_byte(bitsRead);                    
            bitReadPosition = 0;
        }

        if (HT_isALeaf(currentTree))
        {                                                      
            Bit bit = B_getBit(sourceByte, bitReadPosition); 
            if (bit == 0)
                currentTree = currentTree->leftChild;
            else
                currentTree = currentTree->rightChild;
            bitReadPosition++;
        }
        else
        {
            Byte destinationByte = HT_getByte(currentTree);          
            unsigned char naturalToWrite = B_byteToNatural(destinationByte);      
            if (fwrite(&naturalToWrite, sizeof(naturalToWrite), 1, output) != 1) 
                return DECOMPRESS_RESULT_ERROR_FAILED_TO_WRITE_OUTPUT_FILE;
            currentTree = tree; 
            *decompressedSize++;
        }
    }

    return DECOMPRESS_RESULT_OK;
}
