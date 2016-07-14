#ifndef __SYSTEM_FUNCS_H
#define __SYSTEM_FUNCS_H

#include <defs_types.h>

#ifdef __cplusplus
extern "C" {
#endif

void init_seed(unsigned);
BYTE random_byte();



#ifdef __cplusplus
}
#endif

#endif // __SYSTEM_FUNCS_H
