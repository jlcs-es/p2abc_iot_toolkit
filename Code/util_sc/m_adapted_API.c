#include <system_funcs.h>
#include "m_adapted_API.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <crypto_util.h>

///TODO: ordenar por orden alfabético para mejor consulta



/**
 * Generate 8 random bytes stored in \a result
 * @param result Buffer to store the random bytes
 */
void mGetRandomNumber(BYTE result[8]){
    int i;
    for (i = 0; i < 8; i++) {
        result[i] = random_byte() % 256;
    }
}


/**
 * Copy a block of bytes of a fixed length from one location to another.
 * Should work correctly even if the blocks overlap.
 * @param blockLength Number of bytes to copy.
 * @param blockSource Source of bytes to be copied.
 * @param blockDest Destination of copied bytes.
 */
void mBlockCopyFixedLength(BYTE blockLength, BYTE *blockSource, BYTE *blockDest){

//  An alternative multosBlockCopyFixedLength function is implemented that interfaces to the primitive Memory Copy Fixed Length
//  Memory Copy Fixed Length
//    This primitive copies a block of bytes of a fixed length from one location to another.
//    The argument Length is the number of bytes to copy.
//    This primitive works correctly even if the blocks overlap  ///--> memmove vs memcpy
//

    memmove(blockDest, blockSource, blockLength);
    //NOTE: Si memmove no está disponible en todas las plataformas, hacer fachada en system_funcs.h e implementar


}


/**
 *
 * @param sw The parameter is a word value indicating the value of the status word.
 */
void mExitSW(const WORD sw){
    //#define exitSW(w12) \
    //  do { SW12 = w12; __code(__SYSTEM, 4); } while (0)
    //
    //#ifdef __FUNCTION_PROTOTYPES
    //    void multosExitSW (const WORD sw);
    //#else
    //#define multosExitSW(sw) \
    //    __code (__SYSTEM, 5, sw)
    //#endif
    //
    //This function exits smartcard application with status word of sw.

    //FIXME: por ahora imprimimos en stderr, pero debe: terminar la comunicación actual de tarjeta-lector, pero no perder el estado de la tarjeta, como el número de intentos restantes de insertar el pin, etc.
    fprintf(stderr, "%u", sw);
    // TODO: send SW as response to reader.
    // TODO: los tests deberán tener en cuenta el fin de ejecución
    // Note: muchas funciones necesitan que mExitSW termine la ejecución del programa, o al menos petición actual.
}


/**
 * @brief Calculates SHA-256 digest of a message of arbitrary length.
 * The argument for \a hashLen must be 32, for SHA256. In the future other
 * values might be implemented.
 * @param msgLen Lenght of the message to digest
 * @param hashLen Only value supported is 32: SHA256
 * @param hashOut Buffer to save the digest
 * @param msgIn Message to digest
 */
void mSecureHash(WORD msgLen, WORD hashLen, BYTE *hashOut, BYTE *msgIn) {
    if(hashLen != 32)
        return;
    SHA256_CTX ctx;
    sha256_init(&ctx);
    sha256_update(&ctx, msgIn, msgLen);
    sha256_final(&ctx, hashOut);

}