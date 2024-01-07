#include <stdio.h>
#include <stdlib.h>
#include "decompress.h"
#include "compress.h"

#define PROGRAM_NAME "huffman"
#define VERSION "1.0"
#define AUTHORS "John Doe"

#define CLI_RED "\033[1;31m"
#define CLI_NORMAL "\033[0m"

/// Print instructions on how to use the program
void printHelp() {
    printf("%s v%s - by %s\n", PROGRAM_NAME, VERSION, AUTHORS);
    printf("Usage: %s [c|d|h] <filename>\n", PROGRAM_NAME);
    printf("\tc: compress\n");
    printf("\td: decompress\n");
    printf("\th: help\n");
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("%sError, lack of arguments%s\n", CLI_RED, CLI_NORMAL);
        printHelp();
        return EXIT_FAILURE;
    }

    char option = argv[1][0];
    char* filename = argv[2];

    switch (option) {
        case 'c':
            C_compressFile(filename);
            break;
        case 'd':
            D_decompressFile(filename);
            break;
        case 'h':
            printHelp();
            break;
        default:
            printf("%sError, unknown option%s\n", CLI_RED, CLI_NORMAL);
            printHelp();
            return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}