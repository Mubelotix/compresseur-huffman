#include <stdio.h>
#include <stdlib.h>
#include "decompress.h"
#include "compress.h"
#include <unistd.h>
#include <getopt.h>

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
    printf("\n");
    printf("Options:\n");
    printf("-v, --verbosity <level>   Set verbosity level (1 to 3)\n");
    printf("\t0: No output\n");
    printf("\t1: Minimal output\n");
    printf("\t2: Moderate output\n");
    printf("\t3: Verbose output\n");
}

int main(int argc, char *argv[]) {
    int option;
    int verbosity = 2;
    while ((option = getopt(argc, argv, "v:")) != -1) {
        switch (option) {
            case 'v':
                verbosity = atoi(optarg);
                if (verbosity < 0 || verbosity > 3) {
                    fprintf(stderr, "%sError, invalid verbosity level%s\n", CLI_RED, CLI_NORMAL);
                    printHelp();
                    return EXIT_FAILURE;
                }
                break;
            default:
                fprintf(stderr, "%sError, unknown option%s\n", CLI_RED, CLI_NORMAL);
                printHelp();
                return EXIT_FAILURE;
        }
    }
    if (argc - optind != 2) {
        fprintf(stderr, "%sError, incorrect number of arguments%s\n", CLI_RED, CLI_NORMAL);
        printHelp();
        return EXIT_FAILURE;
    }

    char mode = argv[optind][0];
    char *filename = argv[optind + 1];
    switch (mode) {
        case 'c':
            C_compressFile(filename, verbosity);
            break;
        case 'd':
            D_decompressFile(filename, verbosity);
            break;
        case 'h':
            printHelp();
            break;
        default:
            printf("%sError, unknown mode%s\n", CLI_RED, CLI_NORMAL);
            printHelp();
            return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
