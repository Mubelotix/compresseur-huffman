#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H


typedef struct{
    int occurence;
    HT_HuffmanTreeNode* leftChild;
    HT_HuffmanTreeNode* rightChild;
}HT_HuffmanTreeNode;

typedef HT_HuffmanTreeNode* HT_HuffmanTree;


HT_HuffmanTreeNode* HT_getRightChild(HT_HuffmanTreeNode* ht);

HT_HuffmanTreeNode* HT_getLeftChild(HT_HuffmanTreeNode* ht);

B_Byte HT_getByte(HT_HuffmanTreeNode* ht);

int HT_getOccurence(HT_HuffmanTreeNode* ht);

bool HT_isALeaf(HT_HuffmanTreeNode* ht);

HT_HuffmanTreeNode* HT_createLeaf(int occurence);

HT_HuffmanTreeNode* HT_createNode(HT_HuffmanTreeNode* leftChild,HT_HuffmanTreeNode* rightChild)

void HT_destroy(HT_HuffmanTreeNode* ht);

HT_HuffmanTree HT_createTree(HT_HuffmanTreeNode* root)

#endif
