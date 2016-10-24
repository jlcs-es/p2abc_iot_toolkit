#ifndef __CRYPTO_UTIL_H
#define __CRYPTO_UTIL_H

#include "smartcard_common/defs_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************/
/************************** CRYPTO UTIL *****************************/
/********************************************************************/

// TODO : se supone que esto será un adaptador como arithmetic_util y system_funcs
// así que debería definir una interfaz más estándar para el SHA256, AES128 y los que
// vengan, y deje las implementaciones en /smartcard_adaptee junto a mini-gmp y demás
/********************************************************************/
/** */
/* */
/********************************************************************/
/** */
/* */
/********************************************************************/


// SHA256

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



// TODO : cuando venga, el AES se deberá implementar aquí




#ifdef __cplusplus
}
#endif

#endif //__CRYPTO_UTIL_H