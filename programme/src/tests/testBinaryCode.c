#include "binaryCode.h"
#include <CUnit/CUnit.h>
#include "errno.h"

void BC_testLength() {
    BC_BinaryCode bc = BC_binaryCode();
    CU_ASSERT_EQUAL(BC_getLength(bc), 0);

    BC_addBit(&bc, 1);
    CU_ASSERT_EQUAL(BC_getLength(bc), 1);

    BC_addBit(&bc, 0);
    CU_ASSERT_EQUAL(BC_getLength(bc), 2);

    BC_addBit(&bc, 1);
    CU_ASSERT_EQUAL(BC_getLength(bc), 3);
}

void BC_testValues() {
    BC_BinaryCode bc = BC_binaryCode();

    BC_addBit(&bc, 1);
    CU_ASSERT_EQUAL(BC_getBit(bc, 0), 1);

    BC_addBit(&bc, 0);
    CU_ASSERT_EQUAL(BC_getBit(bc, 0), 1);
    CU_ASSERT_EQUAL(BC_getBit(bc, 1), 0);

    BC_addBit(&bc, 1);
    CU_ASSERT_EQUAL(BC_getBit(bc, 0), 1);
    CU_ASSERT_EQUAL(BC_getBit(bc, 1), 0);
    CU_ASSERT_EQUAL(BC_getBit(bc, 2), 1);
}

void BC_testConcat() {
    BC_BinaryCode bc1 = BC_binaryCode();
    BC_BinaryCode bc2 = BC_binaryCode();
    CU_ASSERT_EQUAL(BC_getLength(bc1), 0);
    CU_ASSERT_EQUAL(BC_getLength(bc2), 0);

    // bc1 <- bc1 + bc2
    BC_concatenate(&bc1, &bc2);
    CU_ASSERT_EQUAL(BC_getLength(bc1), 0);
    CU_ASSERT_EQUAL(BC_getLength(bc2), 0);

    // bc1 <- [1]
    // bc1 <- bc1 + bc2 = [1]
    BC_addBit(&bc1, 1);
    BC_concatenate(&bc1, &bc2);
    CU_ASSERT_EQUAL(BC_getLength(bc1), 1);
    CU_ASSERT_EQUAL(BC_getLength(bc2), 0);
    CU_ASSERT_EQUAL(BC_getBit(bc1, 0), 1);

    // bc2 <- [0]
    // bc1 <- bc1 + bc2 = [1, 0]
    BC_addBit(&bc2, 0);
    BC_concatenate(&bc1, &bc2);
    CU_ASSERT_EQUAL(BC_getLength(bc1), 2);
    CU_ASSERT_EQUAL(BC_getLength(bc2), 1);
    CU_ASSERT_EQUAL(BC_getBit(bc1, 0), 1);
    CU_ASSERT_EQUAL(BC_getBit(bc1, 1), 0);

    // bc2 <- bc2 + bc1 = [0, 1, 0]
    BC_concatenate(&bc2, &bc1);
    CU_ASSERT_EQUAL(BC_getLength(bc1), 2);
    CU_ASSERT_EQUAL(BC_getLength(bc2), 3);
    CU_ASSERT_EQUAL(BC_getBit(bc2, 0), 0);
    CU_ASSERT_EQUAL(BC_getBit(bc2, 1), 1);
    CU_ASSERT_EQUAL(BC_getBit(bc2, 2), 0);
}

void BC_testOutOfBounds() {
    BC_BinaryCode bc = BC_binaryCode();

    // Len is 0 but index is 0
    BC_getBit(bc, 0);
    CU_ASSERT_EQUAL(errno, EDOM);
}

void BC_testBufferOverflow() {
    BC_BinaryCode bc = BC_binaryCode();

    // Fill the buffer
    for (int i = 0; i < 256; i++) {
        BC_addBit(&bc, 1);
    }
    CU_ASSERT_EQUAL(BC_getLength(bc), 256);

    // Attempt overflow
    BC_addBit(&bc, 1);
    CU_ASSERT_EQUAL(errno, EOVERFLOW);
    CU_ASSERT_EQUAL(BC_getLength(bc), 256); // the length is unchanged
}
