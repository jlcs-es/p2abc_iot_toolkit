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


#ifdef __cplusplus
}
#endif

#endif //__M_ADAPTED_API_H