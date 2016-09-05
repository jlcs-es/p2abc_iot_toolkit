#ifndef __CRYPTO_UTIL_H
#define __CRYPTO_UTIL_H

#include "defs_types.h"

#ifdef __cplusplus
extern "C" {
#endif



/********************************************************************/
/******************************SHA256********************************/
/********************************************************************/

// MACROS
#define SHA256_BLOCK_SIZE 32            // SHA256 outputs a 32 byte digest

// DATA TYPES

//BYTE; 8-bit byte   //DWORD; 32-bit word
typedef struct {
    BYTE data[64];
    DWORD datalen;
    unsigned long long bitlen;
    DWORD state[8];
} SHA256_CTX;

// FUNCTION DECLARATIONS
void sha256_init(SHA256_CTX *ctx);
void sha256_update(SHA256_CTX *ctx, const BYTE data[], WORD len);
void sha256_final(SHA256_CTX *ctx, BYTE hash[]);




/********************************************************************/
/**********************Big Integer Arithmetic************************/
/********************************************************************/

void shift_right(BYTE *arr, WORD length);
BOOL isZero(BYTE *arr, WORD length);
void fillZeros(BYTE *arr, WORD length);
BOOL isEqual(BYTE *arr1, BYTE *arr2, WORD length);
void copyFromTo(BYTE *src, BYTE *dst, WORD lenght);
void module(BYTE *base, BYTE *modulus, WORD modulusLength);
void modular_add(BYTE *result, BYTE *arr1, BYTE *arr2, BYTE *modulus, WORD length);




#ifdef __cplusplus
}
#endif

#endif //__CRYPTO_UTIL_H