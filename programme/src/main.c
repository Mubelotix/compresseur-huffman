#include <stdio.h>
#include <stdlib.h>
#include "decompress.h"
#include "compress.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Error, lack of arguments");
        return EXIT_FAILURE;
    }

    char option = argv[1][0];
    char* filename = argv[2];

    switch (option) {
        case 'c':
        print('in')
            C_compressFile(filename);
            break;
        //case 'd':
        //    C_decompressFile(filename);
        //    break;
        default:
            printf("Error, character c or d not found");
            return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}