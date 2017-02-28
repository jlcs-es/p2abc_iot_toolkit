#ifndef __SERIALIZE_UTIL_H
#define __SERIALIZE_UTIL_H

#ifdef __cplusplus
extern "C" {
#endif


/********************************************************************/
/************************** SERIALIZE UTIL **************************/
/********************************************************************/

/********************************************************************/
/** Interface for array of bytes serialization storage.             */
/********************************************************************/
/** THIS INTERFACE MAY BE CHANGED FOR TARGET PLATFORM               */
/** ONLY INTERFACE THAT KNOWS THE INTERNAL STRUCTURE OF THE CORE    */
/** MODIFY AS YOU NEED, DEPENDING ON THE STATIC DATA ON THE CORE    */
/** CODE AND THE SERIALIZATION METHOD.                              */
/********************************************************************/

/**
 * Current implementation:
 * Allocates memory and returns the pointer to the
 * json representation of the smartcard's status.
 * @return allocated C string
 */
char* serialize_smartcard_status();

/**
 * Current implementation:
 * Receives a json string and sets all the available
 * static data variables to the values given.
 * @param ascii json text
 */
void deserialize_smartcard_status(unsigned char * ascii);

void serialize_APDU_response(unsigned char* ap_r, int * buf_len);

void deserialize_APDU_command(unsigned char * apdu_bytes, int length);




#ifdef __cplusplus
}
#endif

#endif //__SERIALIZE_UTIL_H