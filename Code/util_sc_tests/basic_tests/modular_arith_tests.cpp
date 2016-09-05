#include <gtest/gtest.h>
#include <crypto_util.h>


TEST(ModularAdditionTest, Test1) {
    WORD length = 1004;
    BYTE result[length];
    BYTE arr1[length];
    BYTE arr2[length];
    BYTE modulus[length];

    fillZeros(result, length);
    

    void modular_add(BYTE *result, BYTE *arr1, BYTE *arr2, BYTE *modulus, WORD length);

}