#include <system_funcs.h>
#include "crypto_help.h"
#include <string.h>

void mGetRandomNumber(BYTE result[8]){
    int i;
    for (i = 0; i < 8; i++) {
        result[i] = random_byte() % 256;
    }
}


void mBlockCopyFixedLength(BYTE blockLength, BYTE *blockSource, BYTE *blockDest){
/**
 * An alternative multosBlockCopyFixedLength function is implemented that interfaces to the primitive Memory Copy Fixed Length
 * Memory Copy Fixed Length
 *   This primitive copies a block of bytes of a fixed length from one location to another.
 *   The argument Length is the number of bytes to copy.
 *   This primitive works correctly even if the blocks overlap  ///--> memmove vs memcpy
 */

    memmove(blockDest, blockSource, blockLength);
    ///Si memmove no está disponible en todas las plataformas, hacer fachada en system_funcs.h e implementar


}