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
    if (noeud == NULL) {
        return;
    }

    // Leaves are saved in the coding table using the current code
    if (HT_isALeaf(noeud)) {
        B_Byte byte = HT_getByte(noeud);
        unsigned int byte2 = B_byteToNatural(byte);
        CT_add(codingTable,byte,code);
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

CT_CodingTable C_buildCodingTable(HT_HuffmanTree tree) {
    CT_CodingTable codingTable = CT_new();
    browseTree(tree, BC_binaryCode(), &codingTable);
    return codingTable;
}

void writeData(FILE* soureFile, FILE* destFile, CT_CodingTable* table) {
    B_Byte byte;
    unsigned int byteNat;
    char inputChar;

    BC_BinaryCode unsavedBits = BC_binaryCode();
    while (fread(&inputChar, 1, 1, soureFile) == 1) {
        byte = B_fromNatural(inputChar);
        BC_BinaryCode newBits = CT_getBinaryCode(*table, byte);
        BC_debug(newBits);
        printf(" ");

        BC_concatenate(&unsavedBits, &newBits);
        
        while (BC_getLength(unsavedBits) >= 8) {
            B_Byte code = BC_removeFirstByte(&unsavedBits);
            unsigned int codeNat = B_byteToNatural(code);
            // print binary
            size_t result = fwrite(&codeNat, sizeof(char), 1, destFile);

            if (result != 1) {
                fprintf(stderr, "Erreur lors de l'écriture des données compressées\n");
                return;
            }
        }
    }
    printf("\n");
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
    printf("\nCounting characters...\n");
    S_Statistics stats = C_computeStatistics(sourceFile);
    S_debug(stats);

    // Order characters by frequency
    printf("\nBuilding priority queue...\n");
    PQ_PriorityQueue queue = PQ_fromStatistics(stats);
    PQ_debug(queue);

    // Build Huffman tree
    printf("\nBuilding Huffman tree...\n");
    HT_HuffmanTree huffmanTree = PQ_intoHuffmanTree(queue);
    HT_debug(huffmanTree);

    // Build coding table
    printf("\nBuilding coding table...\n");
    CT_CodingTable table = C_buildCodingTable(huffmanTree);
    CT_debug(table);

    // Write magic number
    char* id = "HUFFMAN";
    fwrite(id, sizeof(char), strlen(id), tempFile);

    // Save statistics
    S_save(stats, tempFile);

    fseek(sourceFile, 0, SEEK_SET);

    printf("\nWriting data...\n");
    writeData(sourceFile, tempFile, &table); //ecrire donnees compress

    // Fermer les fichiers et libérer la mémoire
    fclose(sourceFile);
    fclose(tempFile);
    
    HT_destroy(huffmanTree);
}
