#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compress.h"
#include "huffmanTree.h"
#include "statistics.h"
#include "codingTable.h"

S_Statistics C_computeStatistics(FILE* nameSourceFile) {
    return;
}

HT_HuffmanTree* C_buildHuffmanTree(S_Statistics stats) {
    return;
}

CT_CodingTable C_buildCodingTable(HT_HuffmanTree* tree) {
    return;
}

void writeStatistics(FILE* file,  S_Statistics* stats) {
    
}

void writeData(FILE* s_file, FILE* d_file, CT_CodingTable* table) {
    
}


void C_compressFile(char* nameSourceFile) {

    //charger fichier source et destination
    FILE* sourceFile = fopen(nameSourceFile, "rb");
    if (sourceFile == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier source.\n");
        exit(EXIT_FAILURE);
    }

    FILE* tempFile = fopen("temp.huff", "wb"); // fichier destination "temp.huff" (a modifier)
    if (tempFile == NULL) {
        fclose(sourceFile);
        fprintf(stderr, "Erreur lors de la création du fichier temporaire.\n");
        exit(EXIT_FAILURE);
    }
    
    // Calcul de la table de codage
    S_Statistics stats = C_computeStatistics(sourceFile);

    HT_HuffmanTree* huffmanTree = C_buildHuffmanTree(stats);

    CT_CodingTable table = C_buildCodingTable(huffmanTree);


    //Remplir le fichier destination
    char* id = "HUFFMAN";  //ecrire l'identifiant ?
    fwrite(id, sizeof(char), strlen(id), tempFile);

    fseek(sourceFile, 0, SEEK_END); //remet le curseur au deb du fichier
    unsigned long lenghtSourecfile = ftell(sourceFile);  // unsigned ou pas
    rewind(sourceFile);

    fwrite(&lenghtSourecfile, sizeof(unsigned long), 1, tempFile); //ecrire la taille

    writeStatistics(tempFile, &stats); //ecrire les stats

    fseek(sourceFile, 0, SEEK_SET);

    writeData(sourceFile, tempFile, &table); //ecrire donnees compress

    // Fermer les fichiers et libérer la mémoire
    fclose(sourceFile);
    fclose(tempFile);
    
    //libererArbreHuffman(huffmanTree);
    //libererTableDeCodage(&table);

    
}
