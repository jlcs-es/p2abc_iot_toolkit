#include <smartcard_utils_interface/crypto_util.h>



/* Implementation using /dev/crypto for HW acceleration */

#ifdef USE_CRYPTODEV

#include <smartcard_external_utilities/cryptodev-SHA256.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

void crypto_InitSeed(DWORD seed){

}

BYTE crypto_RandomByte(){
    return (BYTE)(1 % 256);
}


void crypto_SHA256(BYTE *digest, BYTE *message, WORD length) {
    struct cryptodev_ctx ctx;
    /* Open the crypto device */
    int cfd = open("/dev/crypto", O_RDWR, 0);
    if (cfd < 0) {
        fprintf(stderr, "open(/dev/crypto)");
        return;
    }
    /* Set close-on-exec (not really neede here) */
    if (fcntl(cfd, F_SETFD, 1) == -1) {
        fprintf(stderr, "fcntl(F_SETFD)");
        return;
    }

    sha256_ctx_init(&ctx, cfd, NULL, 0);
    sha256_hash(&ctx, message, length, digest);
    sha256_ctx_deinit(&ctx);

    /* Close the original descriptor */
    if (close(cfd)) {
        perror("close(cfd)");
        return;
    }
}


void crypto_AES128_ECB_Encipher(BYTE *cipherText, BYTE *plainText, BYTE *key) {

}


void crypto_AES128_ECB_Decipher(BYTE *plainText, BYTE *cipherText, BYTE *key) {

}


void crypto_AES128_CBC_Encipher (BYTE *cipherText, BYTE *plainText, WORD inputLength, BYTE *initialValue, BYTE *key){

}


void crypto_AES128_CBC_Decipher (BYTE *plainText, BYTE *cipherText, WORD inputLength, BYTE *initialValue, BYTE *key){

}



#else

/* In this implementation we delegate on the adaptees tiny-AES128 and tiny-SHA256 */

#include <stdlib.h>
#include <smartcard_external_utilities/tiny-AES128.h>
#include <smartcard_external_utilities/tiny-SHA256.h>

void crypto_InitSeed(DWORD seed){
    srand(seed);
}

BYTE crypto_RandomByte(){
    return (BYTE)(rand() % 256);
}


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


void crypto_AES128_CBC_Encipher (BYTE *cipherText, BYTE *plainText, WORD inputLength, BYTE *initialValue, BYTE *key){
    AES128_CBC_encrypt_buffer(cipherText, plainText, inputLength, key, initialValue);
}


void crypto_AES128_CBC_Decipher (BYTE *plainText, BYTE *cipherText, WORD inputLength, BYTE *initialValue, BYTE *key){
    AES128_CBC_decrypt_buffer(plainText, cipherText, inputLength, key, initialValue);
}

#endif