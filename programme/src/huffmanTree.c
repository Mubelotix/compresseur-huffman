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

void HT_debug(HT_HuffmanTree ht) {
    HT_debug_inner(ht, 0, 0);
}

void HT_debug_inner(HT_HuffmanTree ht, unsigned int depth, bool last) {
    if (depth > 0) {
        for (unsigned int i = 0; i < depth-1; i++) {
            printf("│  ");
        }
        if (last) {
            printf("└──");
        } else {
            printf("├──");
        }
    }
    if (HT_isALeaf(ht)) {
        B_Byte byte = HT_getByte(ht);
        unsigned int byteNat = B_byteToNatural(byte);
        printf("Leaf: %d (%d)\n", byteNat, HT_getOccurence(ht));
    } else {
        printf("Node: (%d)\n", HT_getOccurence(ht));
        HT_debug_inner(HT_getLeftChild(ht), depth + 1, 0);
        HT_debug_inner(HT_getRightChild(ht), depth + 1, 1);
    }
}
