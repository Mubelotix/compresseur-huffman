#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compress.h"
#include "huffmanTree.h"
#include "statistics.h"
#include "codingTable.h"

    // 1. Changer type S_Statistics? : tableau d'occurence pour les 256 octets possible
//  typedef struct {
//      int frequencies[256];  
//  } S_Statistics;


    //2. Type HuffmanTreeNode : Faut faire en sorte de stocker l'octet aux feuilles de l'abres
    // soit on met un int valeur qui prend le nb d'occurences et si c une feuille il contient l'octet
    // sinn bah on rajoute un int octet qui prend -1 si c pas une feuille
//struct HT_HuffmanTreeNode {
//    int valeur;
//    struct HT_HuffmanTreeNode* leftChild;
//    struct HT_HuffmanTreeNode* rightChild;
//};

S_Statistics C_computeStatistics(FILE* file) {
    S_Statistics stats;

    stats = S_statistics();

    B_Byte byte;
    while ((byte = fgetc(file)) != EOF) {
        stats->frequencies[byte]++;              // A modifier : fichier d'octet?
    }

    return stats;
}


HT_HuffmanTree C_buildHuffmanTree(S_Statistics stats) {
    HT_HuffmanTree leaves[256];
    for (int i = 0; i < 256; ++i) {
        if (stats->frequencies[i] > 0) {
            leaves[i] = HT_createLeaf(stats->frequencies[i]);
        } else {
            leaves[i] = NULL;
        }
    }

    while (1) {
        // Trouver les deux nœuds avec les fréquences les plus basses
        int min1 = -1, min2 = -1;
        for (int i = 0; i < 256; ++i) {
            if (leaves[i] != NULL) {
                if (min1 == -1 || leaves[i]->valeur < nodes[min1]->valeur) {
                    min2 = min1;
                    min1 = i;
                } else if (min2 == -1 || nodes[i]->valeur < nodes[min2]->valeur) {
                    min2 = i;
                }
            }
        }

        // Si un seul nœud restant, c'est l'arbre de Huffman complet
        if (min2 == -1) {
            return leaves[min1];
        }

        // Créer un nouveau nœud avec la somme des fréquences
        //A noter : pour les 
        HuffmanTree* newNode = createNode(nodes[min1]->valeur + nodes[min2]->valeur);
        newNode->gauche = nodes[min1];
        newNode->droit = nodes[min2];

        // Si un seul nœud restant, c'est l'arbre de Huffman complet
        if (min2 == -1) {
            return nodes[min1];
        }

        // Créer un nouveau nœud avec la somme des fréquences
        HT_HuffmanTree newNode = createNode(nodes[min1]->occurence + nodes[min2]->occurence);
        newNode->leftChild = nodes[min1];
        newNode->rightChild = nodes[min2];

        // Marquer les deux nœuds comme fusionnés
        nodes[min1] = newNode;
        nodes[min2] = NULL;
    }
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
