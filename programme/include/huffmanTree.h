#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H
#include "byte.h"
#define bool int



struct HT_HuffmanTreeNode {
    int octet;  //prend -1 si c un noeud et l'octet si feuille
    int occurence;
    struct HT_HuffmanTreeNode* leftChild;
    struct HT_HuffmanTreeNode* rightChild;
};

typedef struct HT_HuffmanTreeNode* HT_HuffmanTree;


HT_HuffmanTree HT_getRightChild(HT_HuffmanTree ht);

HT_HuffmanTree HT_getLeftChild(HT_HuffmanTree ht);

int HT_getByte(HT_HuffmanTree ht);

int HT_getOctet(HT_HuffmanTree ht);

int HT_getOccurence(HT_HuffmanTree ht);

int HT_isALeaf(HT_HuffmanTree ht);

HT_HuffmanTree HT_createLeaf(int occurence);

HT_HuffmanTree HT_createNode(HT_HuffmanTree leftChild,HT_HuffmanTree rightChild);

void HT_destroy(HT_HuffmanTree ht);

HT_HuffmanTree HT_createTree(HT_HuffmanTree root);

#endif
