#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include "byte.h"
#define bool int

/**
 * @struct HT_HuffmanTreeNode
 * @brief Represents a node in the Huffman tree.
 */
typedef struct HT_HuffmanTreeNode {
    int occurence; ///< The occurrence of the byte in the document.
    B_Byte byte; ///< The value of the byte for leaf nodes.
    struct HT_HuffmanTreeNode *leftChild; ///< The left child of the node.
    struct HT_HuffmanTreeNode *rightChild; ///< The right child of the node.
} HT_HuffmanTreeNode;

/**
 * @typedef HT_HuffmanTree
 * @brief Represents a pointer to a Huffman tree node.
 */
typedef HT_HuffmanTreeNode *HT_HuffmanTree;

/**
 * @brief Returns the right child of the Huffman tree.
 * @param ht The Huffman tree node.
 * @return The right child of the Huffman tree.
 * @exception ENOENT if the Huffman tree is a leaf.
 */
HT_HuffmanTree HT_getRightChild(HT_HuffmanTree ht);

/**
 * @brief Returns the left child of the Huffman tree.
 * @param ht The Huffman tree node.
 * @return The left child of the Huffman tree.
 * @exception ENOENT if the Huffman tree is a leaf.
 */
HT_HuffmanTree HT_getLeftChild(HT_HuffmanTree ht);

/**
 * @brief Returns the byte of the Huffman tree if it is a leaf.
 * @param ht The Huffman tree node.
 * @return The byte of the Huffman tree if it is a leaf.
 * @exception ENOENT if the Huffman tree is not a leaf.
 */
B_Byte HT_getByte(HT_HuffmanTree ht);

/**
 * @brief Returns the occurrence of the Huffman tree.
 * @param ht The Huffman tree node.
 * @return The occurrence of the Huffman tree.
 */
int HT_getOccurence(HT_HuffmanTree ht);

/**
 * @brief Checks whether the Huffman tree is a leaf.
 * @param ht The Huffman tree node.
 * @return Returns true if the Huffman tree is a leaf.
 */
bool HT_isALeaf(HT_HuffmanTree ht);

/**
 * @brief Creates a leaf node for the Huffman tree.
 * @param occurence The number of times the byte appears in the document.
 * @param byte Value of the byte for the leaf node.
 * @return The created leaf node.
 */
HT_HuffmanTree HT_createLeaf(int occurence, B_Byte byte);

/**
 * @brief Creates an internal node for the Huffman tree.
 * @param leftChild The left child of the internal node.
 * @param rightChild The right child of the internal node.
 * @return The created internal node. Remember to destroy it when done.
 * @exception ENOENT if one of the children is NULL.
 */
HT_HuffmanTree HT_createNode(HT_HuffmanTree leftChild, HT_HuffmanTree rightChild);

/**
 * @brief Destroys a Huffman tree, including its children.
 * @param ht The root of the Huffman tree to destroy.
 */
void HT_destroy(HT_HuffmanTree ht);

/**
 * @brief Creates a Huffman tree from a given root node.
 * @param root The root node of the Huffman tree.
 * @return The created Huffman tree.
 */
HT_HuffmanTree HT_createTree(HT_HuffmanTreeNode *root);

/**
 * @brief Outputs debugging information for the Huffman tree.
 * @param ht The Huffman tree to debug.
 */
void HT_debug(HT_HuffmanTree ht);

/**
 * @brief Outputs debugging information for the Huffman tree (internal function).
 * @param ht The Huffman tree to debug.
 * @param depth The current depth in the tree.
 * @param last True if the current node is the last child of its parent.
 */
void HT_debug_inner(HT_HuffmanTree ht, unsigned int depth, bool last);

#endif
