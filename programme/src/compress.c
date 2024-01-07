#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "compress.h"
#include "huffmanTree.h"
#include "statistics.h"
#include "codingTable.h"
#include "binaryCode.h"
#include "priorityQueue.h"

    // 1. Changer type S_Statistics? : tableau d'occurence pour les 256 octets possible (FAIT ✅)
//  typedef struct {
//      int element[256];  
//  } S_Statistics; //(FAIT ✅)


    //(FAIT ✅)//2. Type HuffmanTreeNode : Faut faire en sorte de stocker l'octet aux feuilles de l'abres
    // on rajoute un int octet qui prend -1 si c pas une feuille
//struct HT_HuffmanTreeNode {
//    int occurence;
//    int octet;       //prend -1 si c un noeud et l'octet si feuille
//    struct HT_HuffmanTreeNode* leftChild;
//    struct HT_HuffmanTreeNode* rightChild;
//};
// Et du coup rajouter un getByte dans HT (FAIT ✅)

// 3. Modifier HT_createLeaf de sorte qu'il initialise l'occurence de l'octet (FAIT ✅)

// 4. Modifier HT_createNode de sorte qu'il calcule l'occurence (node.occurence = leftChild.occurence+rightChild.occurence)
//                                      et met node.otet à -1(FAIT ✅)

// 5.  Changer structure CT_CodingTable (FAIT ✅)
// typedef struct {
//    BC_BinaryCode table[256]; // Table de codage pour chaque octet
// } CT_CodingTable;
//Il sera don plus necessaire de passer par CT_coding pour faire l'association entre l'octet et son code binaire 


S_Statistics C_computeStatistics(FILE* file) {
    S_Statistics stats;

    stats = S_statistics();

    B_Byte byte;
    unsigned int byteNat;
    char inputChar;
    while (fread(&inputChar, 1, 1, file) == 1) {
        byteNat = (unsigned int)inputChar;
        byte = B_fromNatural(byteNat);
        S_incCount(&stats, byte);
    }

    return stats;
}

void browseTree(HT_HuffmanTree noeud, BC_BinaryCode code, CT_CodingTable* codingTable) {
    
    if (noeud != NULL) {
        // Si le nœud est une feuille, enregistrez le code binaire dans la table
        if (HT_isALeaf(noeud)) {
            B_Byte byte = HT_getByte(noeud);
            unsigned int byte2 = B_byteToNatural(byte);
            printf("----%d\n",byte2);
            //CT_add(codingTable,byte,code);
            codingTable->tab[byte2].binary_code=code;
            codingTable->tab[byte2].present=1;

        }

        // Parcourir récursivement le sous-arbre gauche avec l'ajout de BC_ZERO au code binaire
        BC_BinaryCode leftCode = code;
        BC_addBit(&leftCode,BC_ZERO);
        HT_HuffmanTree leftChild = HT_getLeftChild(noeud);
        browseTree(leftChild, leftCode, codingTable);

        // Parcourir récursivement le sous-arbre droit avec l'ajout de BC_ONE au code binaire
        BC_BinaryCode rightCode = code;
        BC_addBit(&rightCode,BC_ONE);
        HT_HuffmanTree rightChild = HT_getRightChild(noeud);
        browseTree(rightChild, rightCode, codingTable);
    }
}

CT_CodingTable C_buildCodingTable(HT_HuffmanTree tree) {
    CT_CodingTable codingTable;
    codingTable = CT_new();

    BC_BinaryCode emptyCode = BC_binaryCode();
    
    browseTree(tree, emptyCode, &codingTable);

    return codingTable;
}

void writeStatistics(FILE* file,  S_Statistics* stats) {
    size_t written = fwrite(stats, sizeof(S_Statistics), 1, file);

    // Vérifier si l'écriture a réussi
    if (written != 1) {
        errno = ENOENT; // Erreur d'écriture
    }
}

void writeData(FILE* soureFile, FILE* destFile, CT_CodingTable* table) {
    B_Byte byte;
    unsigned int byteNat;
    char inputChar;
    while (fread(&inputChar, 1, 1, soureFile) == 1){ 
        byte = B_fromNatural(inputChar);
        byteNat = B_byteToNatural(byte);
        BC_BinaryCode code = CT_getBinaryCode(*table,byteNat);
        
        size_t writtenByte = fwrite(&code, sizeof(BC_BinaryCode), 1, destFile);

        // Vérifier si l'écriture a réussi
        if (writtenByte != 1) {
            fprintf(stderr, "Erreur lors de l'écriture des données compressées\n");
            return;
        }
    }
}


void C_compressFile(char* nameSourceFile) {
    printf("Compression du fichier %s...\n", nameSourceFile);

    //Charger fichier source et destination
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
    
    // Count characters
    printf("Counting characters...\n");
    S_Statistics stats = C_computeStatistics(sourceFile);
    unsigned long total = 0;
    for (int i = 0; i < 256; i++) {
        B_Byte byte = B_fromNatural(i);
        if (S_contains(stats, byte) && i != 10) {
            total += S_getCount(stats, byte);
            char associated_char = i;
            printf("\t%c: %d\n", associated_char, S_getCount(stats, byte));
        }
    }
    printf("Total: %lu\n", total);

    PQ_PriorityQueue queue = PQ_fromStatistics(stats);

    HT_HuffmanTree huffmanTree = PQ_intoHuffmanTree(queue);

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
