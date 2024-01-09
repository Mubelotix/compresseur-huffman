#include "codingTable.h"
#include <errno.h>

CT_CodingTable CT_new() {
    CT_CodingTable table;
    for (unsigned int i = 0; i < MAX; i++) {
        table.tab[i].present = 0;
    }
    return table;
}

bool CT_isEmpty(CT_CodingTable table) {
    for (unsigned int i = 0; i < MAX; i++) {
        if (table.tab[i].present) {
            return 0;
        }
    }
    return 1;
}

bool CT_contains(CT_CodingTable table, B_Byte byte) {
    return table.tab[B_byteToNatural(byte)].present;
}

void CT_add(CT_CodingTable *table, B_Byte byte, BC_BinaryCode code) {
    if (table->tab[B_byteToNatural(byte)].present) {
        errno = EEXIST;
        return;
    }
    table->tab[B_byteToNatural(byte)].binary_code = code;
    table->tab[B_byteToNatural(byte)].present = 1;
}

BC_BinaryCode CT_getBinaryCode(CT_CodingTable table, B_Byte byte) {
    if (!table.tab[B_byteToNatural(byte)].present) {
        errno = ENOENT;
        return BC_binaryCode();
    }
    return table.tab[B_byteToNatural(byte)].binary_code;
}

B_Byte CT_getByte(CT_CodingTable table, BC_BinaryCode code) {
    for (unsigned int i = 0; i < MAX; i++) {
        if (table.tab[i].present && BC_equals(table.tab[i].binary_code, code)) {
            return B_fromNatural(i);
        }
    }
    errno = ENOENT;
    return B_byte(0, 0, 0, 0, 0, 0, 0, 0);
}

void browseTree(HT_HuffmanTree noeud, BC_BinaryCode code, CT_CodingTable *codingTable) {
    if (noeud == NULL) {
        return;
    }

    // Leaves are saved in the coding table using the current code
    if (HT_isALeaf(noeud)) {
        B_Byte byte = HT_getByte(noeud);
        CT_add(codingTable, byte, code);
    }

    // Parcourir récursivement le sous-arbre gauche avec l'ajout de BC_ZERO au code binaire
    BC_BinaryCode leftCode = code;
    BC_addBit(&leftCode, BC_ZERO);
    HT_HuffmanTree leftChild = HT_getLeftChild(noeud);
    browseTree(leftChild, leftCode, codingTable);

    // Parcourir récursivement le sous-arbre droit avec l'ajout de BC_ONE au code binaire
    BC_BinaryCode rightCode = code;
    BC_addBit(&rightCode, BC_ONE);
    HT_HuffmanTree rightChild = HT_getRightChild(noeud);
    browseTree(rightChild, rightCode, codingTable);
}

CT_CodingTable CT_fromHuffmanTree(HT_HuffmanTree tree) {
    CT_CodingTable codingTable = CT_new();
    browseTree(tree, BC_binaryCode(), &codingTable);
    return codingTable;
}

void CT_debug(CT_CodingTable table) {
    printf("Coding table:\n");
    for (unsigned int i = 0; i < MAX; i++) {
        if (table.tab[i].present) {
            printf("\t%d: ", i);
            BC_debug(table.tab[i].binary_code);
            printf("\n");
        }
    }
}
