#include <gtest/gtest.h>
#include <crypto_util.h>


/********************************************************************/
/******************************SHA256********************************/
/********************************************************************/

class SHA256Test : public ::testing::Test {
protected:

    BYTE buf[SHA256_BLOCK_SIZE];
    SHA256_CTX ctx;

    virtual void SetUp(){
        sha256_init(&ctx);
    }
};


TEST_F(SHA256Test, abc) {
    BYTE text[] = {"abc"};
    BYTE hash[SHA256_BLOCK_SIZE] = {0xba,0x78,0x16,0xbf,0x8f,0x01,0xcf,0xea,0x41,0x41,0x40,0xde,0x5d,0xae,0x22,0x23,
                                     0xb0,0x03,0x61,0xa3,0x96,0x17,0x7a,0x9c,0xb4,0x10,0xff,0x61,0xf2,0x00,0x15,0xad};
    sha256_update(&ctx, text, strlen((const char *) text));
    sha256_final(&ctx, buf);
    for (int i = 0; i < SHA256_BLOCK_SIZE; i++)
        EXPECT_EQ(hash[i], buf[i]);
}


TEST_F(SHA256Test, abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq) {
    BYTE text[] = {"abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"};
    BYTE hash[SHA256_BLOCK_SIZE] = {0x24,0x8d,0x6a,0x61,0xd2,0x06,0x38,0xb8,0xe5,0xc0,0x26,0x93,0x0c,0x3e,0x60,0x39,
                                     0xa3,0x3c,0xe4,0x59,0x64,0xff,0x21,0x67,0xf6,0xec,0xed,0xd4,0x19,0xdb,0x06,0xc1};
    sha256_update(&ctx, text, strlen((const char *) text));
    sha256_final(&ctx, buf);
    for (int i = 0; i < SHA256_BLOCK_SIZE; i++)
        EXPECT_EQ(hash[i], buf[i]);
}



TEST_F(SHA256Test, aaaaaaaaaax100000) {
    BYTE text[] = {"aaaaaaaaaa"};
    BYTE hash[SHA256_BLOCK_SIZE] = {0xcd,0xc7,0x6e,0x5c,0x99,0x14,0xfb,0x92,0x81,0xa1,0xc7,0xe2,0x84,0xd7,0x3e,0x67,
                                     0xf1,0x80,0x9a,0x48,0xa4,0x97,0x20,0x0e,0x04,0x6d,0x39,0xcc,0xc7,0x11,0x2c,0xd0};
    int idx;
    for (idx = 0; idx < 100000; ++idx)
        sha256_update(&ctx, text, strlen((const char *) text));
    sha256_final(&ctx, buf);
    for (int i = 0; i < SHA256_BLOCK_SIZE; i++)
        EXPECT_EQ(hash[i], buf[i]);
}


TEST_F(SHA256Test, Rosettacode) {
    BYTE text[] = {"Rosetta code"};
    BYTE hash[SHA256_BLOCK_SIZE] = {0x76, 0x4f, 0xaf, 0x5c, 0x61, 0xac, 0x31, 0x5f, 0x14, 0x97, 0xf9, 0xdf, 0xa5,
                                    0x42, 0x71, 0x39, 0x65, 0xb7, 0x85, 0xe5, 0xcc, 0x2f, 0x70, 0x7d, 0x64, 0x68,
                                    0xd7, 0xd1, 0x12, 0x4c, 0xdf, 0xcf};
    sha256_update(&ctx, text, strlen((const char *) text));
    sha256_final(&ctx, buf);
    for (int i = 0; i < SHA256_BLOCK_SIZE; i++)
        EXPECT_EQ(hash[i], buf[i]);
}



/********************************************************************/
/**********************Big Integer Arithmetic************************/
/********************************************************************/


TEST(BigIntegerArithmeticTest, ShiftRight){
    BYTE buffer[8] = {0b10000000, 0b11100101, 0b00011000, 0b11111111, 0b00000000, 0b01010101, 0b10101010, 0b00110011};
    BYTE expBuf[8] = {0b01000000, 0b01110010, 0b10001100, 0b01111111, 0b10000000, 0b00101010, 0b11010101, 0b00011001};
    shift_right(buffer, 8);
    for (int i = 0; i < 8; i++)
        EXPECT_EQ(expBuf[i], buffer[i]);
}