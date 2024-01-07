#include "huffmanTree.h"
#include <stdlib.h>
#include <errno.h>


HT_HuffmanTree HT_getRightChild(HT_HuffmanTree ht) {
    if (!HT_isALeaf(ht)) {
        return ht->rightChild;
    }
    errno = ENOENT;
    return NULL;
}

HT_HuffmanTree HT_getLeftChild(HT_HuffmanTree ht) {
    if (!HT_isALeaf(ht)) {
        return ht->leftChild;
    }
    errno = ENOENT;
    return NULL;
}

int HT_getOccurence(HT_HuffmanTree ht) {
    return ht->occurence;
}

B_Byte HT_getByte(HT_HuffmanTree ht){
    if (HT_isALeaf(ht)) {
        return ht->byte;
    }
    errno = ENOENT;
    return B_byte(0, 0, 0, 0, 0, 0, 0, 0);
}

int HT_isALeaf(HT_HuffmanTree ht) {
    return ((ht->leftChild == NULL) && (ht->rightChild == NULL));
}

HT_HuffmanTree HT_createLeaf(int occurence, B_Byte byte) {
    HT_HuffmanTreeNode* node = (HT_HuffmanTreeNode*)malloc(sizeof(HT_HuffmanTreeNode));
    node->occurence = occurence;
    node->byte = byte;
    node->leftChild = NULL;
    node->rightChild = NULL;
    return node;
}

HT_HuffmanTree HT_createNode(HT_HuffmanTree leftChild, HT_HuffmanTree rightChild) {
    if ((leftChild != NULL) && (rightChild != NULL)) {
        HT_HuffmanTreeNode* node = (HT_HuffmanTreeNode*)malloc(sizeof(HT_HuffmanTreeNode));
        node->occurence = leftChild->occurence + rightChild->occurence;
        node->leftChild = leftChild;
        node->rightChild = rightChild;
        return node;
    } else {
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

HT_HuffmanTree HT_createTree(HT_HuffmanTreeNode* root) {
    return root;
}
