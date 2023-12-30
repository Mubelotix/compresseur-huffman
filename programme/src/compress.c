#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void compressFile(char* nameSourceFile) {

    FILE* sourceFile = fopen(nameSourceFile, "rb");
    if (sourceFile == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier source.\n");
        exit(EXIT_FAILURE);
    }

    FILE* tempFile = fopen("temp.huff", "wb");
    if (tempFile == NULL) {
        fclose(sourceFile);
        fprintf(stderr, "Erreur lors de la création du fichier temporaire.\n");
        exit(EXIT_FAILURE);
    }
    
    S_Statistics stats = computeStatistics(sourceFile);

    HT_HuffmanTree* huffmanTree = buildHuffmanTree(stats);

    CT_CodingTable table = codingTable(huffmanTree);

    const char* id = "HUFFMAN";  //ecrire l'identifiant ?
    fwrite(id, sizeof(char), strlen(id), tempFile);

    fseek(sourceFile, 0, SEEK_END);
    unsigned long lenghtSourecfile = ftell(sourceFile);  // unsigned ou pas
    rewind(sourceFile);

    fwrite(&lenghtSourecfile, sizeof(unsigned long), 1, tempFile);

    writeStatistics(tempFile, &stats);

    //-------------------------------------------
    // 8. Réinitialiser la position du fichier source
    fseek(fichierSource, 0, SEEK_SET);

    // 9. Écrire les données compressées dans le fichier temporaire
    compresserDonnees(fichierSource, fichierTemp, &table);

    // 10. Fermer les fichiers et libérer la mémoire
    fclose(fichierSource);
    fclose(fichierTemp);
    libererArbreHuffman(arbreHuffman);
    libererTableDeCodage(&table);

    // 11. Remplacer le fichier source par le fichier temporaire
    remove(nomFichierSource);  // Supprimer l'ancien fichier source
    rename("temp.huff", nomFichierSource);  // Renommer le fichier temporaire
}
