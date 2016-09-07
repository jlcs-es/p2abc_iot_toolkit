#ifndef __BIG_INTEGER_ARITHMETIC_H
#define __BIG_INTEGER_ARITHMETIC_H

#include "defs_types.h"


/********************************************************************/
/**********************Big Integer Arithmetic************************/
/********************************************************************/

void shift_right(BYTE *arr, WORD length);
void fillZeros(BYTE *arr, WORD length);
void copyFromTo(BYTE *src, BYTE *dst, WORD lenght);

BOOL isZero(BYTE *arr, WORD length);
BOOL isEqual(BYTE *arr1, BYTE *arr2, WORD length);
BOOL isGreater(BYTE *arr1, BYTE *arr2, WORD length);

void module(BYTE *result, BYTE *base, BYTE *modulus, WORD modulusLength);
void subtract(BYTE *result, BYTE *arr1, BYTE *arr2, WORD length);
void modular_add(BYTE *result, BYTE *arr1, BYTE *arr2, BYTE *modulus, WORD length);
void product(BYTE *result, BYTE *arr1, BYTE *arr2, WORD length);
void modular_product(BYTE *result, BYTE *arr1, BYTE *arr2, BYTE *modulus, WORD length);
void modular_exponentiation(WORD exponentLength, WORD modulusLength, BYTE *exponent, BYTE *modulus, BYTE *base, BYTE *result);

#endif //__INTEGER_ARITHMETIC_H

/**
 * This is a simple facade for the needed Big Integer Arithmetic in the
 * virtual smartcard. It can be implemented with optimized code depending
 * on the platform, f.e. arm asm code, 32/64bit machines, etc.
 *
 * The generic implementation works with arrays of bytes and multos'
 * data types defined in defs_types.h (S/BYTE, S/WORD, S/DWORD)
 */

// FIXME: delete methods not used by the m_adapted_API directly, i.e. the real facade