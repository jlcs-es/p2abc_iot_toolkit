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

void add(BYTE *result, BYTE *arr1, BYTE *arr2, WORD length)
{
    // Suppose result's length as length+1

    WORD carry = 0;
    for(WORD i=length-1; i>0; --i){      // Big Endian
        carry = arr1[i] + arr2[i] + carry;
        result[i+1] = carry & 0xFF;
        carry = carry >> 8;
    }
    carry = arr1[0] + arr2[0] + carry; // WORD is unsigned, so testing i>=0 in the for loop does not stop the loop
    result[1] = carry & 0xFF;
    carry = carry >> 8;
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

    // Suppose result's length as double the length argument

//      http://www.geeksforgeeks.org/divide-and-conquer-set-2-karatsuba-algorithm-for-fast-multiplication/
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


    //   Karatsuba with base case a WORD (2 bytes) storing result in a DWORD (4 bytes)

    // Base case
    if(length <= 2){
        WORD num1 = 0;
        WORD num2 = 0;
        if(length == 2){
            num1 += arr1[0] << 8;
            num2 += arr2[0] << 8;
        }
        num1 += arr1[1];
        num2 += arr2[1];

        DWORD product = num1 * num2;

        for(WORD i = 0; i < 4; i++){    //Fixme
            result[i] = product >> ((3-i)*8);
        }
        return;
    }

    // Divide and conquer

    WORD m2 = length/2;
    WORD l; // Max between m2 or length-m2
    BYTE offset = 0; // When copying the halves, the upper half may need an offset if m2<length-m2
    if(m2 == length-m2){
        l = m2;
    } else { // m2 = length/2, so length-m2 is the highest
        l = length-m2;
        offset = 1;
    }

    BYTE high1[l], low1[l];
    BYTE high2[l], low2[l];

    copyFromTo(arr1, high1+offset, m2);
    copyFromTo(arr2, high2+offset, m2);
    if(offset){
        high1[0] = 0;
        high2[0] = 0;
    }
    copyFromTo(arr1+m2, low1, length-m2);
    copyFromTo(arr2+m2, low2, length-m2);

    // end division of arrays


    BYTE z0[l*2];
    BYTE z1[(l+1)*2];
    BYTE z2[l*2];

    product(z0, low1, low2, length-m2); // z0 = karatsuba(low1,low2)
    product(z2, high1, high2, m2); // z2 = karatsuba(high1,high2)

    // z1 = karatsuba((low1+high1),(low2+high2))
    BYTE aux1[l+1], aux2[l+2];
    add(aux1, low1, high1, l);
    add(aux2, low2, high2, l);
    product(z1, aux1, aux2, l+1);
    subtract(z1, z1, z2, l+1); //FIXME: z2 mide l !!
    subtract(z1, z1, z0, l+1); //FIXME: z0 mide l !!

    // return (z2*10^(2*m2))+((z1-z2-z0)*10^(m2))+(z0)



    // Combine the three products to get the final result.
    // return P1*(1<<(2*sh)) + (P3 - P1 - P2)*(1<<sh) + P2; sh = length-m2
    // return P1 << 2*sh + (P3-P1-P2) << sh + P2

    // comparar con la de gmplib porque indica una posible optimización de ahorrarse una suma

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