#include <smartcard_common/m_adapted_API.h>
#include <smartcard_common/defs_errs.h>
#include <smartcard_utils_interface/system_funcs.h>
#include <smartcard_utils_interface/crypto_util.h>
#include <smartcard_utils_interface/arithmetic_util.h>



void mAESECBDecipher (BYTE *cipherText, BYTE *plainText, BYTE keyLength, BYTE *key){
    if(keyLength != 16) // Only implemented AES128
        return; // TODO: avisar de error de implementación
    crypto_AES128_ECB_Decipher(plainText, cipherText, key);
}

void mAESECBEncipher (BYTE *plainText, BYTE *cipherText, BYTE keyLength, BYTE *key){
    if(keyLength != 16) // Only implemented AES128
        return; // TODO: avisar de error de implementación
    crypto_AES128_ECB_Encipher(cipherText, plainText, key);
    // BYTE *plaintext: address of 16 bytes of plaintext (input) -> tiny-AES128 hace los ECB en bloques de 16bytes  -> OK
}


void mBlockAdd (const WORD blockLength, BYTE *block1, BYTE *block2, const BYTE *result){
    addition(result, block1, block2, blockLength);
}


void mBlockCopyFixedLength(BYTE blockLength, BYTE *blockSource, BYTE *blockDest){
    mem_move(blockDest, blockSource, blockLength);
}


void mBlockDecipherCBC (const BYTE algorithm, WORD inputLength, BYTE *cipherText, BYTE *plainText,
                              BYTE initialValueLength, BYTE *initialValue, BYTE keyLength, BYTE *key){

    //   AlgorithmID : 0x06  AES
    if(algorithm != 0x06)
        return;
    //  Key Length : 16bytes=128bits AES128
    if(keyLength != 16)
        return;
    //  Initial Value Length : 16 bytes AES
    if(initialValueLength != 16)
        return;

    crypto_AES128_CBC_Decipher (plainText, cipherText, inputLength, initialValue, key);

}


void mBlockEncipherCBC (const BYTE algorithm, WORD inputLength, BYTE *plainText, BYTE *cipherText,
                              BYTE initialValueLength, BYTE *initialValue, BYTE keyLength, BYTE *key){

    //   AlgorithmID : 0x06  AES
    if(algorithm != 0x06)
        return;
    //  Key Length : 16bytes=128bits AES128
    if(keyLength != 16)
        return;
    //  Initial Value Length : 16 bytes AES
    if(initialValueLength != 16)
        return;

    crypto_AES128_CBC_Encipher (cipherText, plainText, inputLength, initialValue, key);
}


void mBlockMultiply (const WORD blockLength, BYTE *block1, BYTE *block2, BYTE *result){
    multiplication(result, block1, block2, blockLength);
}



void mBlockSubtract (const WORD blockLength, BYTE *block1, BYTE *block2, const BYTE *result){
    subtraction(result, block2, block1, blockLength);
    //    NOTE: result = block2 - block1
    //    This function subtracts the value found in block1 to that found in block2 and places the difference
    //    in the block indicated in result.
}

BOOL mCheckCase (BYTE isoCase){
    //TODO : se hará junto a los Exit, cuando tengamos la interfaz que define cómo recibimos
    // los APDUs y por tanto podremos saber cómo analizarlos.
    /**
     * Remarks
ISO/IEC 7816 – 4 describes the four possible command cases. In brief, they are:
Case    Command Data Sent   Response Data Expected
1       No                  No
2       No                  Yes
3       Yes                 No
4       Yes                 Yes
Once an incoming command has been identified by the application as being one that it can process,
     Check Case should be called using the expected ISO command case as the stack based parameter.
     If the data in public is consistent with the expected command case, the CCR Z flag will be set
     and cleared otherwise. If the ISOCase parameter is not a valid command case indicator the primitive
     will consider this to be an inconsistency and clear the CCR Z flag.
The operating system’s handling of a Case 1 command is such that only a status word is returned.
     There are, however, some interface devices that expect an acknowledgement byte to be transmitted
     prior to the status word. In order to cater for these devices both MULTOS 4 and MULTOS 4.2 support
     an ISOCase parameter value of 5. The handling of this case value is exactly the same as that
     for Case 1 with the exception that an acknowledgement byte is transmitted.
The amount of APDU command checking that can be performed by the primitive is based on the transport
     protocol in use. In most cases an application does not need to be aware of the low level transport
     handling that occurs as MULTOS ensures that it is takes place. In those cases where more information
     is required, please see [MDG].
     */


    return 1;
}

void mExit (void){
    //Default SW 0x9000  ERR_OK
    //TODO
    // NOTE: en las variables globales están también SW, La, etc., y serán las que hay que asignar aquí y llamar a
    // una función que genere los bytes de respuesta y llame a la función de IO que envíe la respuesta y de por
    // terminado la ejecución de la tarjeta
}
void mExitLa (const BYTE la){
    //TODO
}
void mExitSW(const WORD sw){
    //TODO
}
void mExitSWLa (const WORD sw, const BYTE la){
    //TODO
}


void mGetRandomNumber(BYTE result[8]){
    int i;
    for (i = 0; i < 8; i++) {
        result[i] = crypto_RandomByte() % 256;
    }
}



void mModularExponentiation (WORD exponentLength, WORD modulusLength, BYTE *exponent, BYTE *modulus, BYTE *input, BYTE *output) {
    if (exponentLength > modulusLength)
        mExitSW(ERR_EXPONENT_LARGER_THAN_MODULUS); // From crxModularExponentiation original implementation
    modularExponentiation(output, input, exponent, modulus, modulusLength, exponentLength);
}



void mModularMultiplication (WORD modulusLength, BYTE *modulus, BYTE *block1, BYTE *block2){
    modularMultiplication(block1, block1, block2, modulus, modulusLength);
}


void mModularReduction (WORD operandLength, WORD modulusLength, BYTE *operand, BYTE *modulus){
    modularReduction(operand, operand, modulus, operandLength, modulusLength);
}


void mSecureHash(WORD msgLen, WORD hashLen, BYTE *hashOut, BYTE *msgIn) {
    if(hashLen != 32)
        return; // TODO: avisar de error de implementación
    crypto_SHA256(hashOut, msgIn, hashLen);
}


