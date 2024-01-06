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

bool CT_contains(CT_CodingTable table, unsigned int octet) {
    return table.tab[octet].present;
}

void CT_add(CT_CodingTable* table, unsigned int octet, BC_BinaryCode code) {
    if (table->tab[octet].present) {
        errno = EEXIST;
        return;
    }
    table->tab[octet].binary_code = code;
    table->tab[octet].present = 1;
}

BC_BinaryCode CT_getBinaryCode(CT_CodingTable table, unsigned int octet) {
    if (!table.tab[octet].present) {
        errno = ENOENT;
        return BC_binaryCode();
    }
    return table.tab[octet].binary_code;
}

B_Byte CT_getByte(CT_CodingTable table, BC_BinaryCode code) {
    for (unsigned int i = 0; i < MAX; i++) {
        if (table.tab[i].present && BC_equals(table.tab[i].binary_code, code)) {
            return B_byte(i & 0x80, i & 0x40, i & 0x20, i & 0x10, i & 0x08, i & 0x04, i & 0x02, i & 0x01);
        }
    }
    errno = ENOENT;
    return B_byte(0, 0, 0, 0, 0, 0, 0, 0);
}
