#include <crypto_util.h>

/*
 *
 *
#define SHA256(digest, plaintext_length, plaintext)	\
do {							\
  __push(__typechk(unsigned int, plaintext_length));	\
  __push(__typechk(unsigned int, 32));			\
  __push(__typechk(unsigned char *, digest));	\
  __push(__typechk(unsigned char *, plaintext)); 	\
  __code(__PRIM, 0xcf);					\
} while (0)

MDRM
 Secure Hash
This primitive calculates the SHA-1, SHA-224, SHA-256, SHA-384 or SHA-512
 digest of a message of arbitrary length in accordance with [FIPS180-3].


 *
 *
 */


/// TODO: en vez de usar SHA256, implementar la adaptación de la API SecureHash de multos
/// (SHA: Secure Hash Algorithm), que es la llamada 0xcf más el valor 32