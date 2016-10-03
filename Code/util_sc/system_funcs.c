#include "system_funcs.h"

#include <stdlib.h>
#include <string.h>


void init_seed(unsigned seed){
    srand(seed);
}


BYTE random_byte(){
/*
 * System specific implementation.
 * Change it with the Contiki library when needed.
 */
    return (BYTE)(rand() % 256);
}


void mem_move(BYTE * destination, BYTE * source, BYTE num){

    memmove(destination, source, num);

}