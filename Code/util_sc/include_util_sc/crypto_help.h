#ifndef __CRYPTO_HELP_
#define __CRYPTO_HELP_

#include "defs_types.h"


#ifdef __cplusplus
extern "C" {
#endif

void mGetRandomNumber(BYTE result[8]);
void mBlockCopyFixedLength(BYTE blockLength, BYTE *blockSource, BYTE *blockDest);


#ifdef __cplusplus
}
#endif

#endif //__CRYPTO_HELP_