#include <smartcard_adaptor/system_funcs.h>
#include <smartcard_common/m_adapted_API.h>
#include <smartcard_adaptor/crypto_util.h>
#include <smartcard_adaptor/arithmetic_util.h>

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


void mBlockMultiply (const WORD blockLength, BYTE *block1, BYTE *block2, BYTE *result){

    multiplication(result, block1, block2, blockLength);

}



void mBlockAdd (const WORD blockLength, BYTE *block1, BYTE *block2, const BYTE *result){

    addition(result, block1, block2, blockLength);

}


void mBlockSubtract (const WORD blockLength, BYTE *block1, BYTE *block2, const BYTE *result){

    subtraction(result, block2, block1, blockLength);
    //    NOTE: result = block2 - block1
    //    This function subtracts the value found in block1 to that found in block2 and places the difference
    //    in the block indicated in result.

}




void mAESECBEncipher (BYTE *plainText, BYTE *cipherText, BYTE keyLength, BYTE *key){

}






///////////////////////




//      multosAESECBEncipher(temp_buffer+16, temp_buffer+32, 16, temp_buffer);

//
//    void multosAESECBEncipher (BYTE *plainText, BYTE *cipherText,
//                               BYTE keyLength, BYTE *key)
//    The parameters are:
//     BYTE *plaintext: address of 16 bytes of plaintext (input)
//     BYTE *cipherText: address of buffer to hold ciphertext (output)
//     BYTE keyLength: length of key in bytes (input)
//     BYTE *key: address of key to use (input)
//    This is an interface to the primitive AES ECB Encipher.


// Note : como usa un keylength de 16 es compatible con tiny-AES128-C de github




/////////////////////



//    // buffer = buffer1 || ... || buffer_d where size(buffer_i) = 16 bytes
//
//    // crxAESEncryptCBC(BYTE *ciphertext, const BYTE *iv, const BYTE *plaintext, WORD plaintext_size, const BYTE *key)
//    crxAESEncryptCBC(temp_buffer+80, temp_buffer+64, buffer, buffer_size, temp_buffer+48);





//
//        #define crxAESEncryptCBC(ciphertext, iv, plaintext, plaintext_size, key) \
//        do \
//        { \
//            __push (__typechk(BYTE, 0x10)); \
//            __push (__typechk(BYTE *, iv)); \
//            __push (__typechk(WORD, plaintext_size)); \
//            __push (__typechk(BYTE *, key)); \
//            __push (__typechk(BYTE, 0x10)); \
//            __push (__typechk(BYTE *, ciphertext)); \
//            __push (__typechk(BYTE *, plaintext)); \
//            __code (__PRIM, 0xDB, 0x06, 0x02); \
//        } while (0)
//
//        // crxAESDecryptCBC(BYTE *plaintext, const BYTE *iv, const BYTE *ciphertext, WORD ciphertext_size, const BYTE *key)
//        #define crxAESDecryptCBC(plaintext, iv, ciphertext, ciphertext_size, key) \
//        do \
//        { \
//            __push (__typechk(BYTE, 0x10)); \
//            __push (__typechk(BYTE *, iv)); \
//            __push (__typechk(WORD, ciphertext_size)); \
//            __push (__typechk(BYTE *, key)); \
//            __push (__typechk(BYTE, 0x10)); \
//            __push (__typechk(BYTE *, plaintext)); \
//            __push (__typechk(BYTE *, ciphertext)); \
//            __code (__PRIM, 0xDA, 0x06, 0x02); \
//        } while (0)
//

//
//    AES ECB Decipher
//            This primitive performs AES ECB Decipher on a sixteen byte block of memory in accordance with [FIPS197].
//    PRIM 0xD6 NOTE : no es el mismo codigo
//
//    The 2 byte parameter KeyAddr is the starting address of the AES key to be used.
//    The 1 byte parameter KeyLen is the length in bytes of the AES key at address KeyAddr.
//    The 2 byte parameter OutputAddr is the starting address of the resultant 16-bytes of plaintext.
//    The 2 byte parameter InputAddr is the starting address of the 16-bytes of ciphertext.

//*****//


//    Block Decipher
//    This primitive performs a Block Decipher on a block of memory.
// The algorithms that may be used are DES, Triple DES, SEED and AES in ECB and CBC modes of operation.
//
//  PRIM 0xDA, AlgorithmID, ChainingMode


//   AlgorithmID : 0x06  AES
//   Chaining Mode :  0x02  CBC


// NOTE: CBC !! - si la clave es de 16bytes, 128bits, nos servirá tiny-AES128-C de github

//  CBC mode
//  CBC mode requires the addition of an Initialisation Vector of length
// equal to the block size for the selected algorithm.
// The size of the Initialisation Vector depends upon the specified algorithm, as follows.
// AES: 16 bytes
// The stack for this mode is:
// IVLen : 0x10 = 16  ->  NOTE por AES??? pero no indica tamaño de clave, y no indica AES, eso lo indica 0x06 de AlgorithmID
// IV
//  InputLen specifies the number of bytes to decipher.  : plaintext_size / ciphertext_size
//  KeyAddr is the address of the key(s) to be used. : key
//
// The size and format of the key at this address depends upon the specified algorithm, as follows.
//  AES : one 16, 24 or 32 byte AES key.
//
//  KeyLen is the length in bytes of the key at address KeyAddr.  :  0x10  =  16bytes = NOTE AES128 !!!  nos servirá tiny-AES128-C de github OK !!!

//  OutputAddr is the starting address of the resultant plaintext
//  InputAddr is the start address of the ciphertext to be deciphered


// NOTE   AES- 128 algorithms require that the ciphertext is a multiple of 16 bytes. If the ciphertext length does not meet these restrictions then the primitive will abend. Padding is not removed during the block decipher operation.
// NOTE   AES- 128 algorithms require that the plaintext is a multiple of 16 bytes. If the plaintext length does not meet these restrictions then the primitive will abend.


//*******//

//
//    void multosBlockEncipherCBC (const BYTE algorithm, WORD inputLength,
//                                 BYTE *plainText, BYTE *cipherText,
//                                 BYTE initialValueLength, BYTE *initialValue, BYTE keyLength, BYTE *key);
//    The parameters are:
//     const BYTE algorithm: 0x03 = DES, 0x04 = 3DES, 0x05 = SEED, 0x06 = AES 128bit (input)
//     WORD inputLength: Length of plainText (input)
//     BYTE *plainText: pointer to plain text to encipher (input)
//     BYTE *cipherText: pointer to memory in which to write the cipher text output. (output)
//     BYTE initialValueLength: length of the Initial Chaining Vector pointed to by initialValue (input)
//     BYTE *initialValue: Pointer to ICV value (input)
//     BYTE keyLength: length of key, depends on algorithm being used (input)
//     BYTE *key: pointer to the key to use (input)
//    This function enciphers the cipher text using the cipher block chaining method and supports a number of algorithms.
//    This is an interface to the primitive Block Encipher.


//
//



// NOTE : Solución, es para los crx multosBlockEncipherCBC con claves de 16 bytes (AES128)
// NOTE : Solución, para multosAESECBEncipher, el que es, con sólo la opción de AES128 implementada (tipo el sha256 de más arriba)
// NOTE : Se usa en SmartCard AES  ECB y CBC, pero siempre de 128bits, por lo que el proyecto de github sirve perfectamente a este caso






















// Note : Decisión de usar WORD y que no se necesite crxBlockMultiply127/128/256
// como el cast sería de unsigned 8 bit a unsigned 16 bit es compatible con su uso de la CAPI


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


