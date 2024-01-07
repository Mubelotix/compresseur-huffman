#ifndef DECOMPRESS_H
#define DECOMPRESS_H

/**
 * @brief Decompresses a file.
 * @param nameSourceFile The name of the source file to be decompressed.
 * @param verbosity Level of verbosity for the decompression process.
 *                   0: Minimal output, 1: Standard output, 2: Verbose output.
 */
void D_decompressFile(char* nameSourceFile, int verbosity);

#endif
