#ifndef __ARITHMETIC_UTIL_H
#define __ARITHMETIC_UTIL_H

#include "defs_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************/
/**********************Big Integer Arithmetic************************/
/********************************************************************/


/********************************************************************/
/** This a a simple facade for the needed Big Integer Arithmetic in */
/* the virtual smartcard. It can be implemented as desired, with    */
/* optimized code code depending on the platform.                   */
/********************************************************************/
/** A software generic BYTE array implementation is provided so it  */
/* works in any platform, prioritizing memory usage. Of course, this*/
/* implementation will be slower than any platform specific code.   */
/********************************************************************/


/**
 * Calculates result = arr1 * arr2
 * @param result Array of size 2*length. Stores the solution.
 * @param arr1 Array of size length. First factor.
 * @param arr2 Array of size length. Second factor.
 * @param length
 */
void multiplication(BYTE *result, BYTE *arr1, BYTE *arr2, WORD length);


/**
 * Calculates result = ( arr1 * arr2 ) mod modulus
 * @param result Array of size length. Stores the solution.
 * @param arr1 Array of size length. First factor. Does not need to be reduced modulus.
 * @param arr2 Array of size length. Second factor. Does not need to be reduced modulus.
 * @param modulus Array of size length. Stores the modulus value.
 * @param length
 */
void modularMultiplication(BYTE *result, BYTE *arr1, BYTE *arr2, BYTE *modulus, WORD length);


/**
 * Calculates result = ( base ^ exponent ) mod modulus
 * @param result Array of size modulusLength. Stores the solution.
 * @param base Array of size modulusLength. Base of the exponentiation.
 * @param exponent Array of size exponentLength. Power of the exponentiation.
 * @param modulus Array of size modulusLength. Stores the modulus value.
 * @param modulusLength
 * @param exponentLength
 */
void modularExponentiation(BYTE *result, BYTE *base, BYTE *exponent, BYTE *modulus, WORD modulusLength, WORD exponentLength);


#ifdef __cplusplus
}
#endif

#endif //__ARITHMETIC_UTIL_H
