#include "huffmanTree.h"
#include <stdlib.h>

struct HT_HuffmanTreeNode* HT_getRightChild(struct HT_HuffmanTreeNode* ht) {
    // Précondition: ht n'est pas une feuille
    if (!HT_isALeaf(ht)) {
        return ht->rightChild;
    }
    return NULL;
}

struct HT_HuffmanTreeNode* HT_getLeftChild(struct HT_HuffmanTreeNode* ht) {
    // Précondition: ht n'est pas une feuille
    if (!HT_isALeaf(ht)) {
        return ht->leftChild;
    }
    return NULL;
}

B_Byte HT_getByte(struct HT_HuffmanTreeNode* ht) {
    // Précondition: ht est une feuille
        return ht->occurence;
}

int HT_getOccurence(struct HT_HuffmanTreeNode* ht) {
    return ht->occurence;
}

bool HT_isALeaf(struct HT_HuffmanTreeNode* ht) {
    return ((ht->leftChild == NULL) && (ht->rightChild == NULL));
}

struct HT_HuffmanTreeNode* HT_createLeaf(int occurence) {
    struct HT_HuffmanTreeNode* node = (struct HT_HuffmanTreeNode*)malloc(sizeof(struct HT_HuffmanTreeNode));
    node->occurence = occurence;
    node->leftChild = NULL;
    node->rightChild = NULL;
    return node;
}

struct HT_HuffmanTreeNode* HT_createNode(struct HT_HuffmanTreeNode* leftChild, struct HT_HuffmanTreeNode* rightChild) {
    // Précondition: leftChild et rightChild ne sont pas nuls
    if ((leftChild != NULL) && (rightChild != NULL)) {
        struct HT_HuffmanTreeNode* node = (struct HT_HuffmanTreeNode*)malloc(sizeof(struct HT_HuffmanTreeNode));
        node->occurence = leftChild->occurence + rightChild->occurence;
        node->leftChild = leftChild;
        node->rightChild = rightChild;
        return node;
    }
}

void HT_destroy(struct HT_HuffmanTreeNode* ht) {
    if (ht != NULL) {
        HT_destroy(ht->leftChild);
        HT_destroy(ht->rightChild);
        free(ht);
    }
}

HT_HuffmanTree HT_createTree(struct HT_HuffmanTreeNode* root) {
    // Précondition: root n'est pas nul
    if (root != NULL) {
        return root;
    }
}
