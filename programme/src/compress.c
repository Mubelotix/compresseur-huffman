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
    // on rajoute un int octet qui prend -1 si c pas une feuille
//struct HT_HuffmanTreeNode {
//    int valeur;
//    int octet;       //prend -1 si c un noeud et l'octet si feuille
//    struct HT_HuffmanTreeNode* leftChild;
//    struct HT_HuffmanTreeNode* rightChild;
//};
// Et du coup rajouter un getOctet dans HT

// 3. Modifier HT_createLeaf de sorte qu'il initialise la valeur de l'octet

// 4. Modifier HT_createNode de sorte qu'il calcule la valeur (node.valeur = leftChild.valeur+rightChild.valeur)
//                                      et met node.otet à -1

// 5.  Changer structure CT_CodingTable
// typedef struct {
//    BC_BinaryCode table[256]; // Table de codage pour chaque octet
// } CT_CodingTable;
//Il sera don plus necessaire de passer par CT_coding pour faire l'association entre l'octet et son code binaire 



S_Statistics C_computeStatistics(FILE* file) {
    S_Statistics stats;

    stats = S_statistics();

    B_Byte byte;
    while ((byte = fgetc(file)) != EOF) {       // si c un fichier d'octet faut trouver l'equivalent de fgetc
        stats->frequencies[byte]++;              // A modifier : fichier d'octet et freaquencies prend un [int] ?
    }

    return stats;
}


HT_HuffmanTree C_buildHuffmanTree(S_Statistics stats) {
    HT_HuffmanTree nodes[256];
    for (int i = 0; i < 256; ++i) {
        if (stats->frequencies[i] > 0) {
            nodes[i] = HT_createLeaf(stats->frequencies[i]);     
        } else {
            nodes[i] = NULL;
        }
    }

    while (1) {
        // Trouver les deux nœuds avec les fréquences les plus basses
        int min1 = -1, min2 = -1;
        for (int i = 0; i < 256; ++i) {
            if (nodes[i] != NULL) {
                if (min1 == -1 || nodes[i]->valeur < nodes[min1]->valeur) {
                    min2 = min1;
                    min1 = i;
                } else if (min2 == -1 || nodes[i]->valeur < nodes[min2]->valeur) {
                    min2 = i;
                }
            }
        }

        // Si un seul nœud restant, c'est l'arbre de Huffman complet
        if (min2 == -1) {
            return nodes[min1];
        }

        // Créer un nouveau nœud avec la somme des fréquences
        HuffmanTree newNode = createNode(nodes[min1], nodes[min2]);

        // Fusionner les 2 noeuds
        nodes[min1] = newNode;
        nodes[min2] = NULL;
    }
}

void browseTree(HuffmanTree* noeud, BC_BinaryCode code, CT_CodingTable* codingTable) {
    
    if (noeud != NULL) {
        // Si le nœud est une feuille, enregistrez le code binaire dans la table
        if (HT_isALeaf(noeud)) {
            codingTable->table[noeud->octet] = code;  //rajouter un getOctet dans HT et modifier CT_add pour l'utiliser ici
        }

        // Parcourir récursivement le sous-arbre gauche avec l'ajout de BC_ZERO au code binaire
        BC_BinaryCode leftCode = code;
        BC_addBit(&leftCode,BC_ZERO);
        browseTree(HT_getLeftChild(noeud), leftCode, codingTable);

        // Parcourir récursivement le sous-arbre droit avec l'ajout de BC_ONE au code binaire
        BC_BinaryCode rightCode = code;
        BC_addBit(&rightCode,BC_ONE);
        browseTree(HT_getRightChild(noeud), codeDroite, codingTable);
    }
}

CT_CodingTable C_buildCodingTable(HT_HuffmanTree* tree) {
    CT_CodingTable codingTable;
    for (int i = 0; i < 256; ++i) {
        // Initialiser chaque BC_BinaryCode à zéro bits
        codingTable.table[i] = BC_binaryCode();
    }

    BC_BinaryCode emptyCode = BC_binaryCode();
    
    browseTree(tree, emptyCode, &codingTable);

    return codingTable;
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