#ifndef __CRYPTO_UTIL_H
#define __CRYPTO_UTIL_H

#include "smartcard_common/defs_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************/
/************************** CRYPTO UTIL *****************************/
/********************************************************************/

/********************************************************************/
/** This a a simple adapter for the needed crypto functions in      */
/* the virtual smartcard. It can be implemented as desired, with    */
/* optimized code code depending on the platform.                   */
/********************************************************************/
/** This implementation is based on 'tiny' versions of the crypto   */
/* algorithms, with no random operations security, or other good    */
/* practices. In constrained devices HW support could be added with */
/* external modules (e.g. Atmos).                                   */
/********************************************************************/


/**
 * Calculate SHA256 digest of message
 * digest = 32 bytes/256 bits array of SHA256(length bytes long message)
 * @param digest buffer to store the SHA256 digest
 * @param message byte array of \param length bytes long
 * @param length
 */
void crypto_SHA256(BYTE *digest, BYTE *message, WORD length);


/**
 * Encrypt plainText 16 bytes block with AES128 ECB Mode and 128 bits key
 * cipherText = 16 bytes long AES128 ECB Mode enciphered data in plainText
 * @param cipherText (output)
 * @param plainText Address of 16 bytes of plaintext (input)
 * @param key (input)
 */
void crypto_AES128_ECB_Encipher(BYTE *cipherText, BYTE *plainText, BYTE *key);


/**
 * Decrypt cipherText 16 bytes block with AES128 ECB Mode and 128 bits key
 * plainText = 16 bytes long AES128 ECB Mode deciphered data in cipherText
 * @param plainText (output)
 * @param cipherText Address of 16 bytes of ciphertext(input)
 * @param key (output)
 */
void crypto_AES128_ECB_Decipher(BYTE *plainText, BYTE *cipherText, BYTE *key);

// TODO : AES128 CBC


#ifdef __cplusplus
}
#endif

#endif //__CRYPTO_UTIL_H