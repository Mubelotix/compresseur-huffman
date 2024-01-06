#include "statistics.h"
#include "huffmanTree.h"
#include "binaryCode.h"
#include <string.h>

bool isFileCompressed(FILE *input)
{
    char identifier[4];
    if (fread(identifier, sizeof(char), sizeof(identifier), input) != 4)
        return false;

    if (strncmp(identifier, "HUFF", sizeof(identifier)) != 0)
        return false;

    return true;
}