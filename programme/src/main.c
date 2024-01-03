int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Error, lack of arguments");
        return EXIT_FAILURE;
    }

    char option = argv[1][0];
    const char* filename = argv[2];

    switch (option) {
        case 'c':
            C_compressFile(filename);
            break;
        case 'd':
            C_decompressFile(filename);
            break;
        default:
            printf("Error, character c or d not found");
            return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}