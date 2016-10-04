#include <system_funcs.h>
#include <m_adapted_API.h>
#include <crypto_util.h>
#include <arithmetic_util.h>
// TODO: quitar:
#include <stdio.h>

// TODO : ordenar por orden alfabético para mejor consulta
// TODO : llevar el doxygen al .h



/**
 * Generate 8 random bytes stored in \a result
 * @param result Buffer to store the random bytes
 */
void mGetRandomNumber(BYTE result[8]){
    int i;
    for (i = 0; i < 8; i++) {
        result[i] = random_byte() % 256;
    }
}


/**
 * Copy a block of bytes of a fixed length from one location to another.
 * Should work correctly even if the blocks overlap.
 * @param blockLength Number of bytes to copy.
 * @param blockSource Source of bytes to be copied.
 * @param blockDest Destination of copied bytes.
 */
void mBlockCopyFixedLength(BYTE blockLength, BYTE *blockSource, BYTE *blockDest){

    mem_move(blockDest, blockSource, blockLength);

}


/**
 *
 * @param sw The parameter is a word value indicating the value of the status word.
 */
void mExitSW(const WORD sw){
    //#define exitSW(w12) \
    //  do { SW12 = w12; __code(__SYSTEM, 4); } while (0)
    //
    //#ifdef __FUNCTION_PROTOTYPES
    //    void multosExitSW (const WORD sw);
    //#else
    //#define multosExitSW(sw) \
    //    __code (__SYSTEM, 5, sw)
    //#endif
    //
    //This function exits smartcard application with status word of sw.

    //FIXME: por ahora imprimimos en stderr, pero debe: terminar la comunicación actual de tarjeta-lector, pero no perder el estado de la tarjeta, como el número de intentos restantes de insertar el pin, etc.
    fprintf(stderr, "%u", sw);
    // TODO: send SW as response to reader.
    // TODO: los tests deberán tener en cuenta el fin de ejecución
    // Note: muchas funciones necesitan que mExitSW termine la ejecución del programa, o al menos petición actual.
}


/**
 * @brief Calculates SHA-256 digest of a message of arbitrary length.
 * The argument for \a hashLen must be 32, for SHA256. In the future other
 * values might be implemented.
 * @param msgLen Lenght of the message to digest
 * @param hashLen Only value supported is 32: SHA256
 * @param hashOut Buffer to save the digest
 * @param msgIn Message to digest
 */
void mSecureHash(WORD msgLen, WORD hashLen, BYTE *hashOut, BYTE *msgIn) {
    if(hashLen != 32)
        return;
    SHA256_CTX ctx;
    sha256_init(&ctx);
    sha256_update(&ctx, msgIn, msgLen);
    sha256_final(&ctx, hashOut);

}


/**    4.79 multosModularExponentiation
 *   void multosModularExponentiation (WORD exponentLength, WORD modulusLength, BYTE *exponent, BYTE *modulus, BYTE *input, BYTE *output)
 * This function performs a modular exponentiation.
 * Note that the values held at modulus, input and output are all considered to be of size modulusLength.
 * @param exponentLength: the length of the exponent used
 * @param modulusLength: the length of the modulus
 * @param exponent: address of the exponent
 * @param modulus: address of the modulus
 * @param input: address of the input value
 * @param output: address of where to write the result of the operation
 */
void mModularExponentiation (WORD exponentLength, WORD modulusLength, BYTE *exponent, BYTE *modulus, BYTE *input, BYTE *output) {

    if (exponentLength > modulusLength)
        mExitSW(0x9F30); // From crxModularExponentiation original implementation

    modularExponentiation(output, input, exponent, modulus, modulusLength, exponentLength);

}


void mModularReduction (WORD operandLength, WORD modulusLength, BYTE *operand, BYTE *modulus){

    modularReduction(operand, operand, modulus, operandLength, modulusLength);

}


void mModularMultiplication (WORD modulusLength, BYTE *modulus, BYTE *block1, BYTE *block2){

    modularMultiplication(block1, block1, block2, modulus, modulusLength);

}

/////
// TODO : funciones a falta de ser adaptadas:
//////

///
//  USO encontrado: único
//

//    // void multosModularMultiplication (WORD modulusLength, BYTE *modulus, BYTE *block1, BYTE *block2);
//    // We set the first bytes of buffer and temp_buffer to 0. This is
//    // necessary for the crxModularMultiplication routine. We expect
//    // temp_modulus to already have zero's on the left-most bytes.
//    memset(buffer, 0, MAX_BIGINT_SIZE-temp_modulus_size);
//    memset(temp_buffer, 0, MAX_BIGINT_SIZE-temp_modulus_size);
//    crxModularMultiplication(temp_modulus_size,   /* modulus size */
//        temp_modulus,        /* modulus */
//        buffer,              /* buffer */
//        temp_buffer);        /* temp   */  // this overwrites buffer
//

// TODO : de los memset podemos (creo) sacar dónde empiezan los bits significativos
// en resumen: crx espera buffers de tamaño fijo donde en el final están los valores, y
// multosCAPI espera arrays ya de tamaño el modulusLength y los maneja tal cual
// Pasar a multosCAPI la dirección de la parte del final del buffer que se le da a
// crx y listo, se puede usar los mismos buffers que el código original pero llamando
// a una función que no depende de ellos.

/*
 * void crxModularMultiplication (WORD mLength, BYTE *m, BYTE *a, BYTE *b)
 *
 * We expect both 'a' and 'b' to be already reduced modulo 'm'.
 *
 * We expect 'a' to be a buffer of size BUFFER_MAX_SIZE, the
 * significant bytes being stored on
 *
 * a[MAX_BIGINT_SIZE-mLength ... MAX_BIGINT_SIZE].
 *
 * Same for 'b'.
 *
 * The result is stored in
 *
 * a[MAX_BIGINT_SIZE-mLength ... MAX_BIGINT_SIZE].
 *
 * We expect 'm' to be a buffer of size MAX_BIGINT_SIZE, the
 * significant bytes being stored on
 *
 * m[MAX_BIGINT_SIZE-mLength ... MAX_BIGINT_SIZE].
 *
 */


/**


 void multosModularMultiplication (WORD modulusLength, BYTE *modulus, BYTE *block1, BYTE *block2)
The parameters are:
 WORD modulusLength: the length of the modulus used
 BYTE *modulus: address of the modulus
 BYTE *block1: address of the first operand
 BYTE *block2: address of the second operand


 This function performs a modular multiplication. The result of the operation is written to block1.


 This is an interface to the primitive Modular Multiplication.


 The result overwrites the first operand.

 */