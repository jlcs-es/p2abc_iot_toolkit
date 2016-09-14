#include <arithmetic_util.h>

/********************************************************************/
/**********************Big Integer Arithmetic************************/
/********************************************************************/


#ifdef MINI_GMP

/********************************************************************/
/*   Implementation of the facade that delegates in miniGMP         */
/********************************************************************/

#include <mini-gmp.h>


void multiplication(BYTE *result, BYTE *arr1, BYTE *arr2, WORD length){
    mpz_t factor1, factor2, rop;
    mpz_init(factor1); mpz_init(factor2); mpz_init(rop);
    mpz_import(factor1, length, 1, sizeof(arr1[0]), 0, 0, arr1);
    mpz_import(factor2, length, 1, sizeof(arr2[0]), 0, 0, arr2);

    mpz_mul(rop, factor1, factor2);

    //FIXME: mpz_export le da igual el tamaño de result, hay que
    //calcular el offset sobre result* para que escriba, y poner
    //el resto a ceros.
    mpz_export(result, NULL, 1, sizeof(result[0]), 0, 0, rop);
}


void modularMultiplication(BYTE *result, BYTE *arr1, BYTE *arr2, BYTE *modulus, WORD length){
    mpz_t factor1, factor2, mod, rop;
    mpz_init(factor1); mpz_init(factor2); mpz_init(mod); mpz_init(rop);
    mpz_import(factor1, length, 1, sizeof(arr1[0]), 0, 0, arr1);
    mpz_import(factor2, length, 1, sizeof(arr2[0]), 0, 0, arr2);
    mpz_import(mod, length, 1, sizeof(modulus[0]), 0, 0, modulus);

    mpz_mod(factor1, factor1, mod);
    mpz_mod(factor2, factor2, mod);
    mpz_mul(rop, factor1, factor2);
    mpz_mod(rop, rop, mod);

    mpz_export(result, NULL, 1, sizeof(result[0]), 0, 0, rop);

}


void modularExponentiation(BYTE *result, BYTE *base, BYTE *exponent, BYTE *modulus, WORD modulusLength, WORD exponentLength){
    mpz_t b, exp, mod, rop;
    mpz_init(b); mpz_init(exp); mpz_init(mod); mpz_init(rop);
    mpz_import(b, modulusLength, 1, sizeof(base[0]), 0, 0, base);
    mpz_import(exp, exponentLength, 1, sizeof(exponent[0]), 0, 0, exponent);
    mpz_import(mod, modulusLength, 1, sizeof(modulus[0]), 0, 0, modulus);

    mpz_powm(rop, b, exp, mod);

    mpz_export(result, NULL, 1, sizeof(result[0]), 0, 0, rop);

}





#else // Default use sw generic provided implementation:

/********************************************************************/
/*   Implementation of the facade that delegates in SW BYTE arrays  */
/* operations.                                                      */
/********************************************************************/

#include <arithmetic_implementation_v1.h>


void multiplication(BYTE *result, BYTE *arr1, BYTE *arr2, WORD length){
    product(result, arr1, arr2, length);
}


void modularMultiplication(BYTE *result, BYTE *arr1, BYTE *arr2, BYTE *modulus, WORD length){
    modular_product(result, arr1, arr2, modulus, length);
}


void modularExponentiation(BYTE *result, BYTE *base, BYTE *exponent, BYTE *modulus, WORD modulusLength, WORD exponentLength){
    modular_exponentiation(result, base, exponent, modulus, modulusLength, exponentLength);
}

#endif