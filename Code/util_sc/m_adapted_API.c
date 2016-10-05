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





// TODO : considerar un API ampliada a razón de estos comentarios:

// compute c * u mod q
// Due to the fact that multosModularMultiplication stores the MSB
// of the result on block1[0] (which is *not* how things should be
// done), we replace this instruction with a simple
// multiplication, followed by a modular reduction.



// Note : crxBlockMultiply### parece ser karatsuba, confirmar





//
//    void multosBlockMultiply (const BYTE blockLength, BYTE *block1, BYTE *block2, BYTE *result)
//    The parameters are:
//     const BYTE blockLength: the size of the operands
//     BYTE *block1: address of the first byte of block1
//     BYTE *block2: address of the first byte of block2
//     BYTE *result: address of the first byte of result
//            This function multiplies the value held in block1 by that held in block2
// and writes the result to the block result of size blockLength + blockLength.
//    This is an interface to the primitive MultiplyN.




// NOTE : el tamaño es un BYTE, no un WORD !!
// Note : Decisión de usar WORD y que no se necesite crxBlockMultiply127/128/256
// como el cast sería de unsigned 8 bit a unsigned 16 bit es compatible con su uso de la CAPI






///////////////////////

//
//    void multosBlockAdd (const BYTE blockLength, BYTE *block1, BYTE *block2, const BYTE *result)
//    The parameters are:
//     const BYTE blockLength: size of the blocks to add.
//     BYTE *block1: address of the first block
//     BYTE *block2: address of the second block
//     const BYTE *result: address of the block that will hold the result of the operation
//    This function adds the value found in block1 to that found in block2 and places the sum
//    in the block indicated in the result parameter.
//
// Note that block1, block2 and result are all considered to be of size blockLength.
//
//
//  This is an interface to the instruction ADDN.


//
//    ADDN
//            This instruction adds the byte-block at the top of the stack to a byte-block specified by the label.
//            If the label is omitted then the top two byte-blocks on the stack are used.
//    Syntax    ADDN [label], block_length
//    Remarks
//        The block_length value is specified using a single byte. Therefore, the maximum length of a block is 255 bytes
//
//    The label, if present, may be either a named memory location, which the assembler will translate into
//            a register / offset pair, or an explicit register / offset pair. If a label is not specified, then the
//            operands of size block_length will be taken from the stack.
//    The result of the addition will be written to the address corresponding to the label or, if no label is given,
//    to the byte block immediately below the topmost block.
//
// In no case is the top byte block changed by the operation.
//
//   The operation will work if the two blocks overlap.
//



// Note : como antes: The block_length value is specified using a single byte.
// Therefore, the maximum length of a block is 255 bytes
// usamos WORD y que sea compatible en el futuro sin usar crx mierdas

// NOTE: The operation will work if the two blocks overlap.









///////////////////////



//
//    void multosBlockSubtract (const BYTE blockLength, BYTE *block1, BYTE *block2, const BYTE *result)
//    The parameters are:
//     const BYTE blockLength: size of the blocks to subtract. Both blocks must be the same size.
//     BYTE *block1: address of the first block
//     BYTE *block2: address of the second block
//     const BYTE *result: address of the block that will hold the result of the operation
//    This function subtracts the value found in block1 to that found in block2 and places the difference
//    in the block indicated in result.
//    This is an interface to the instruction SUBN.



// SUBN
//  The operation will work if the two blocks overlap.

// NOTE: supondremos block2 - block1 como dice la API oficial y poner un FIXME en el código que lo usa y aquí
// como antes: length BYTE a WORD, superponer







///////////////////////




