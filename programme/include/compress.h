#ifndef COMPRESS_H
#define COMPRESS_H

/**
 * @brief Compresses a file.
 * @param nameSourceFile The name of the source file to be compressed.
 * @param verbosity Level of verbosity for the compression process.
 *                   0: Minimal output, 1: Standard output, 2: Verbose output.
 */
void C_compressFile(char* nameSourceFile, int verbosity);

#endif
