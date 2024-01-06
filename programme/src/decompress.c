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