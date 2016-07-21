#include <system_funcs.h>
#include "m_adapted_API.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

///TODO: ordenar por orden alfabético para mejor consulta

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

    ///FIXME: por ahora -salimos* del programa, pero debe llamar a una función que devuelva al lector de tarjetas el código Status Word
    printf("%u", sw);
    exit(sw);
}