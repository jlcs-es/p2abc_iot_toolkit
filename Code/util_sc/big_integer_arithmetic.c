#include "big_integer_arithmetic.h"


/********************************************************************/
/**********************Big Integer Arithmetic************************/
/********************************************************************/

void shift_right(BYTE *arr, WORD length)
{

    WORD i;
    for (i = length-1;  i > 0;  --i)
    {
        arr[i] = (arr[i] >> 1) | ((arr[i-1] << 7) & 128);
    }
    arr[0] = arr[0] >> 1;

}

void fillZeros(BYTE *arr, WORD length)
{
    int i;
    for(i=0; i<length; i++)
    {
        arr[i]=0;
    }
}

void copyFromTo(BYTE *src, BYTE *dst, WORD lenght)
{
    for(WORD i=0; i<lenght; ++i){
        dst[i] = src[i];
    }
}



BOOL isZero(BYTE *arr, WORD length)
{
    int i;
    for(i=0; i<length; i++)
    {
        if(arr[i]!=0)
            return 0;
    }
    return 1;
}

BOOL isEqual(BYTE *arr1, BYTE *arr2, WORD length)
{
    WORD i;
    for(i=0; i<length; i++)
    {
        if(arr1[i]!=arr2[i])
            return 0;
    }
    return 1;
}

BOOL isGreater(BYTE *arr1, BYTE *arr2, WORD length)
{
    for(WORD i=0; i<length; ++i){ //Big endian
        if(arr1[i]>arr2[i])
            return 1;
        if(arr1[i]<arr2[i])
            return 0;
    }
}



/**
 * Calculates result = base mod modulus
 * Allows superposition for buffers
 * @param result
 * @param base
 * @param modulus
 * @param modulusLength
 */
void module(BYTE *result, BYTE *base, BYTE *modulus, WORD modulusLength)
{
    //note: seguramente muy mejorable
    while(isGreater(base, modulus, modulusLength)){
        subtract(result, base, modulus, modulusLength);
    }
}

/**
 * Subtract arr1 - arr2 and store result in result. Allows superposition for buffers.
 * @param result
 * @param arr1
 * @param arr2
 * @param length
 */
void subtract(BYTE *result, BYTE *arr1, BYTE *arr2, WORD length)
{

    SWORD carry = 0;
    BYTE borrow = 0;
    for(WORD i=length-1; i>0; --i){      // Big Endian
        carry = arr1[i] - arr2[i] - borrow;
        borrow = 0;
        if(carry<0) {
            carry += 256; // 0b100000000
            borrow = 1;
        }
        result[i] = carry & 0xFF;
    }
    // WORD is unsigned, so testing i>=0 in the for loop does not stop the loop
    carry = arr1[0] - arr2[0] - borrow;
    if(carry<0) {
        carry += 256; // 0b100000000
    }
    result[0] = carry & 0xFF;
}

void modular_add(BYTE *result, BYTE *arr1, BYTE *arr2, BYTE *modulus, WORD length)
{
    // Apply modulo to the operands
    module(arr1, arr1, modulus, length);
    module(arr2, arr2, modulus, length);

    WORD carry = 0;
    for(WORD i=length-1; i>0; --i){      // Big Endian
        carry = arr1[i] + arr2[i] + carry;
        result[i] = carry & 0xFF;
        carry = carry >> 8;
    }
    carry = arr1[0] + arr2[0] + carry; // WORD is unsigned, so testing i>=0 in the for loop does not stop the loop
    result[0] = carry & 0xFF;
    carry = carry >> 8;

    //  if carry is != 0 after the loop, it means that result can't store the addition initialy and the module will fail
    if(carry!=0){
        // avoid overflows
        BYTE auxArr[length+1];
        copyFromTo(result, auxArr+1, length); //copy result to the last positions of auxArr
        auxArr[0] = carry & 0xFF;
        BYTE auxMod[length+1];
        copyFromTo(modulus, auxMod+1, length);
        auxMod[0] = 0x00;

        module(auxArr, auxArr, auxMod, length+1);
        copyFromTo(auxArr+1, result, length);
    }
    else {
        module(result, result, modulus, length);
    }
}

void product(BYTE *result, BYTE *arr1, BYTE *arr2, WORD length)
{

//    https://en.wikipedia.org/wiki/Karatsuba_algorithm#Pseudocode
//    procedure karatsuba(num1, num2)
//        if (num1 < 10) or (num2 < 10)
//        return num1*num2
//        /* calculates the size of the numbers */
//        m = max(size_base10(num1), size_base10(num2))
//        m2 = m/2
//        /* split the digit sequences about the middle */
//        high1, low1 = split_at(num1, m2)
//        high2, low2 = split_at(num2, m2)
//        /* 3 calls made to numbers approximately half the size */
//        z0 = karatsuba(low1,low2)
//        z1 = karatsuba((low1+high1),(low2+high2))
//        z2 = karatsuba(high1,high2)
//        return (z2*10^(2*m2))+((z1-z2-z0)*10^(m2))+(z0)


    //   Karatsuba with base case a DWORD (4 bytes)


}

/**
 * Stores in result the value of (arr1*arr2) mod modulus
 * Initialy the buffers must not supperpose
 * @param arr1
 * @param arr2
 * @param modulus
 * @param length
 */
void modular_product(BYTE *result, BYTE *arr1, BYTE *arr2, BYTE *modulus, WORD length)
{
    //Module

    //Product

    //Module
}

// TODO: tener en cuenta si las operaciones permiten usar el mismo array de parámetro y salida
// TODO: usar arrays auxiliares para la solución, que no sobrescriban parámetros dados.
// TODO: Una vez funcionen las operaciones, intentar que puedan superponerse los arrays, y entonces
// TODO: sólo habrá que cambiar modular_exp que lo usa, poniendo como buffer de salida uno de los
// TODO: buffers de operador, que es mejor de cara a dar la opción a cómo usarlo y a que sea óptimo cuando pueda.


void modular_exponentiation(WORD exponentLength, WORD modulusLength,
                            BYTE *exponent, BYTE *modulus,
                            BYTE *base, BYTE *result)
{
    fillZeros(result, modulusLength);
    if(isZero(modulus, modulusLength))
    {
        return;     // if modulus = 1 then return 0
    }

    result[modulusLength-1]=1; // result := 1   // Multos is big endian

    module(base, base, modulus, modulusLength);  // base := base mod modulus

    BYTE aux[modulusLength];


    while(!isZero(exponent, exponentLength))    // while exponent > 0
    {
        if((exponent[exponentLength-1] & 1) == 1)   // if (exponent mod 2 == 1):
        {
            modular_product(aux, base, result, modulus, modulusLength);  // result := (result * base) mod modulus
            //todo asign aux to ..
        }

        shift_right(exponent, exponentLength);  // exponent := exponent >> 1

        modular_product(aux, base, base, modulus, modulusLength);    // base := (base * base) mod modulus
        //todo asign aux to ..

    }

    // return result

}