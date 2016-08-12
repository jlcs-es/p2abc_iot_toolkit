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

///TODO: ordenar por orden alfabético para mejor consulta


void mGetRandomNumber(BYTE result[8]);
void mBlockCopyFixedLength(BYTE blockLength, BYTE *blockSource, BYTE *blockDest);
void mExitSW(const WORD sw);
void mSecureHash(WORD msgLen, WORD hashLen, BYTE *hashOut, BYTE *msgIn);


#ifdef __cplusplus
}
#endif

#endif //__M_ADAPTED_API_H