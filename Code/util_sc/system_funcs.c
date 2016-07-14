/*
* System: x86
*/

/*
 * System specific implementation.
 * Change it with the Contiki library when needed.
 */

#include "system_funcs.h"
#include <stdlib.h>
#include <time.h>


void init_seed(unsigned seed){
    srand(seed);
}


BYTE random_byte(){
    return (BYTE)(rand() % 256);
}