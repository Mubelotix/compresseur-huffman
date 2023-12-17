#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H
#include "byte.h"
#define bool int



struct HT_HuffmanTreeNode {
    int occurence;
    struct HT_HuffmanTreeNode* leftChild;
    struct HT_HuffmanTreeNode* rightChild;
};

typedef struct HT_HuffmanTreeNode* HT_HuffmanTree;


struct HT_HuffmanTreeNode* HT_getRightChild(struct HT_HuffmanTreeNode* ht);

struct HT_HuffmanTreeNode* HT_getLeftChild(struct HT_HuffmanTreeNode* ht);

B_Byte HT_getByte(struct HT_HuffmanTreeNode* ht);

int HT_getOccurence(struct HT_HuffmanTreeNode* ht);

bool HT_isALeaf(struct HT_HuffmanTreeNode* ht);

struct HT_HuffmanTreeNode* HT_createLeaf(int occurence);

struct HT_HuffmanTreeNode* HT_createNode(struct HT_HuffmanTreeNode* leftChild,struct HT_HuffmanTreeNode* rightChild);

void HT_destroy(struct HT_HuffmanTreeNode* ht);

HT_HuffmanTree HT_createTree(struct HT_HuffmanTreeNode* root);

#endif
