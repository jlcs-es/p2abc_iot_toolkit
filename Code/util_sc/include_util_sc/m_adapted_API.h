/**
 * ADAPTED MULTOS CAPI
 * Multos' C API adapted to be used in our software smartcard.
 * Only the needed functions were implemented.
 * Every adapted function changes its name from multosFooBar() to mFooBar()
 */

#ifndef __M_ADAPTED_API_H
#define __M_ADAPTED_API_H

#include "defs_types.h"


#ifdef __cplusplus
extern "C" {
#endif

// TODO: ordenar por orden alfabético para mejor consulta


/********************************************************************/
/********************** Multos Adapted C API ************************/
/********************************************************************/


/********************************************************************/
/** This a Multos C API adaptation, restricted to the functions     */
/* used in the P2ABC SW smartcards. The functions must be the same  */
/* as in the CAPI documentation, changing multos for m              */
/********************************************************************/
/** Provided implementation is in C, only depending on other        */
/* provided files, so it can be platform independent.               */
/********************************************************************/

void mGetRandomNumber(BYTE result[8]);
void mBlockCopyFixedLength(BYTE blockLength, BYTE *blockSource, BYTE *blockDest);
void mExitSW(const WORD sw);
void mSecureHash(WORD msgLen, WORD hashLen, BYTE *hashOut, BYTE *msgIn);
void mModularExponentiation (WORD exponentLength, WORD modulusLength, BYTE *exponent, BYTE *modulus, BYTE *input, BYTE *output);
void mModularReduction (WORD operandLength, WORD modulusLength, BYTE *operand, BYTE *modulus);
void mModularMultiplication (WORD modulusLength, BYTE *modulus, BYTE *block1, BYTE *block2);


#ifdef __cplusplus
}
#endif

#endif //__M_ADAPTED_API_H