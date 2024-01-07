#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H
#include "byte.h"
#define bool int

typedef struct {
    int occurence;
    B_Byte byte;
    struct HT_HuffmanTreeNode* leftChild;
    struct HT_HuffmanTreeNode* rightChild;
} HT_HuffmanTreeNode;

typedef HT_HuffmanTreeNode* HT_HuffmanTree;

/// @brief Returns the right child of the Huffman tree
/// @return The right child of the Huffman tree.
/// @exception ENOENT if the Huffman tree is a leaf.
HT_HuffmanTree HT_getRightChild(HT_HuffmanTree ht);

/// @brief Returns the left child of the Huffman tree
/// @return The left child of the Huffman tree.
/// @exception ENOENT if the Huffman tree is a leaf.
HT_HuffmanTree HT_getLeftChild(HT_HuffmanTree ht);

/// @brief Returns the byte of the Huffman tree if it is a leaf.
/// @return The byte of the Huffman tree if it is a leaf.
/// @exception ENOENT if the Huffman tree is not a leaf.
B_Byte HT_getByte(HT_HuffmanTree ht);

/// @brief Returns the occurence of the Huffman tree, which is the sum of the occurences of its children.
/// @return The occurence of the Huffman tree.
int HT_getOccurence(HT_HuffmanTree ht);

/// @brief Checks whether the Huffman tree is a leaf.
/// @return Returns true if the Huffman tree is a leaf
bool HT_isALeaf(HT_HuffmanTree ht);

/// @brief Create a leaf
/// @param occurence The number of times the byte appears in the document
/// @param byte Value of the byte of the leaf
/// @return The leaf
HT_HuffmanTree HT_createLeaf(int occurence, B_Byte byte);

/// @brief Create a node from two children.
/// @param leftChild The left child of the node
/// @param rightChild The right child of the node
/// @return The created node. Please don't forget to destroy it once you are done using it.
/// @exception ENOENT if one of the children is NULL.
HT_HuffmanTree HT_createNode(HT_HuffmanTree leftChild, HT_HuffmanTree rightChild);

/// @brief Destroy a Huffman tree. Will destroy the children recursively.
/// @param ht The root of the Huffman tree to destroy.
void HT_destroy(HT_HuffmanTree ht);

HT_HuffmanTree HT_createTree(HT_HuffmanTreeNode* root);

void HT_debug(HT_HuffmanTree ht);
void HT_debug_inner(HT_HuffmanTree ht, unsigned int depth, bool last);

#endif
