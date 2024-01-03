#include "huffmanTree.h"
#include <stdlib.h>
#include <errno.h>


HT_HuffmanTree HT_getRightChild(HT_HuffmanTree ht) {
    // Précondition: ht n'est pas une feuille
    if (!HT_isALeaf(ht)) {
        return ht->rightChild;
    }
    return NULL;
}

HT_HuffmanTree HT_getLeftChild(HT_HuffmanTree ht) {
    // Précondition: ht n'est pas une feuille
    if (!HT_isALeaf(ht)) {
        return ht->leftChild;
    }
    return NULL;
}

int HT_getByte(HT_HuffmanTree ht) {
    // Précondition: ht est une feuille
        return ht->occurence;
}

int HT_getOccurence(HT_HuffmanTree ht) {
    return ht->occurence;
}

bool HT_isALeaf(HT_HuffmanTree ht) {
    return ((ht->leftChild == NULL) && (ht->rightChild == NULL));
}

HT_HuffmanTree HT_createLeaf(int occurence) {
    HT_HuffmanTree node = (HT_HuffmanTree)malloc(sizeof(struct HT_HuffmanTreeNode));
    node->occurence = occurence;
    node->leftChild = NULL;
    node->rightChild = NULL;
    return node;
}

HT_HuffmanTree HT_createNode(HT_HuffmanTree leftChild, HT_HuffmanTree rightChild) {
    // Précondition: leftChild et rightChild ne sont pas nuls
    if ((leftChild != NULL) && (rightChild != NULL)) {
        HT_HuffmanTree node = (HT_HuffmanTree)malloc(sizeof(struct HT_HuffmanTreeNode));
        node->occurence = leftChild->occurence + rightChild->occurence;
        node->leftChild = leftChild;
        node->rightChild = rightChild;
        return node;
    }
    else{
        errno = ENOENT;
        return NULL;
    }
}

void HT_destroy(HT_HuffmanTree ht) {
    if (ht != NULL) {
        HT_destroy(ht->leftChild);
        HT_destroy(ht->rightChild);
        free(ht);
    }
}

HT_HuffmanTree HT_createTree(HT_HuffmanTree root) {
    // Précondition: root n'est pas nul
    if (root != NULL) {
        return root;
    }
    else{
        return NULL;
    }
}
