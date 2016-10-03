#ifndef __SYSTEM_FUNCS_H
#define __SYSTEM_FUNCS_H

#include <defs_types.h>

#ifdef __cplusplus
extern "C" {
#endif


/********************************************************************/
/********************** System std Functions ************************/
/********************************************************************/


/********************************************************************/
/** This a a simple facade for some functions that can be HW        */
/* dependent and usually implemented in standard libraries
/********************************************************************/
/** This version implements with std libraries, but with this       */
/* facade, it is easier for not std compatible systems to implement */
/* their own version (f.e. sensor based random), without having to  */
/* modify the core of this SC solution.                             */
/********************************************************************/



void init_seed(unsigned);

/**
 * Returns a random 8bit BYTE
 * @return
 */
BYTE random_byte();


/**
 * Copy a block of bytes of a fixed length from one location to another.
 * Should work correctly even if the blocks overlap.
 * @param destination   Pointer to the destination array where the content is to be copied.
 * @param source        Pointer to the source of data to be copied.
 * @param num           Number of bytes to copy.
 */
void mem_move(BYTE * destination, BYTE * source, BYTE num);


void mem_cmp();

void mem_cpy();

void mem_set();


#ifdef __cplusplus
}
#endif

#endif // __SYSTEM_FUNCS_H
