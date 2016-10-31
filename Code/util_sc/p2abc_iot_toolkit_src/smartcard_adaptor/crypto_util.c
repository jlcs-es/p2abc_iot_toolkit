#include <smartcard_adaptor/crypto_util.h>


/* In this implementation we delegate on the adaptees tiny-AES128 and tiny-SHA256 */

#include <smartcard_adaptee/tiny-AES128.h>
#include <smartcard_adaptee/tiny-SHA256.h>


void crypto_SHA256(BYTE *digest, BYTE *message, WORD length) {
    SHA256_CTX ctx;
    sha256_init(&ctx);
    sha256_update(&ctx, message, length);
    sha256_final(&ctx, digest);
}

void crypto_AES128_ECB_Encipher(BYTE *cipherText, BYTE *plainText, BYTE *key) {
    AES128_ECB_encrypt(plainText, key, cipherText);
}

void crypto_AES128_ECB_Decipher(BYTE *plainText, BYTE *cipherText, BYTE *key) {
    AES128_ECB_decrypt(cipherText, key, plainText);
}