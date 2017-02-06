#ifndef __DEBUG_H
#define __DEBUG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "smartcard_common/defs_types.h"


void imprimirHexadecimal(BYTE *buffer, int length);
void imprimirMensaje(char * msg);

#ifdef __cplusplus
}
#endif

#endif