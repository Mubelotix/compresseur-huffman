#include <CUnit/CUnit.h>
#include "codingTable.h"
#include "byte.h"


void CT_testIsEmpty() {
    CT_CodingTable table;
    table.length = 0;

    CU_ASSERT_TRUE(CT_isEmpty(table));
}

void CT_testLength() {
    CT_CodingTable table;
    table.length = 5;

    CU_ASSERT_EQUAL(CT_lenght(table),5);
}

void CT_testContainsAndAdd() {
    CT_CodingTable table = CT_codingTable();

}

/*
void testAddAndContains() {
    CodingTable table = codingTable();
    Byte byteToAdd = 65;  // Exemple de byte à ajouter
    BinaryCode codeToAdd = "0101";  // Exemple de code binaire à ajouter

    assert(!contains(table, byteToAdd));

    add(&table, byteToAdd, codeToAdd);

    assert(contains(table, byteToAdd));
    assert(length(table) == 1);
}

void testGetBinaryCode() {
    CodingTable table = codingTable();
    Byte byteToAdd = 65;
    BinaryCode codeToAdd = "0101";

    add(&table, byteToAdd, codeToAdd);

    assert(getBinaryCode(table, byteToAdd) == codeToAdd);
}

void testGetByte() {
    CodingTable table = codingTable();
    Byte byteToAdd = 65;
    BinaryCode codeToAdd = "0101";

    add(&table, byteToAdd, codeToAdd);

    assert(getByte(table, codeToAdd) == byteToAdd);
}


*/