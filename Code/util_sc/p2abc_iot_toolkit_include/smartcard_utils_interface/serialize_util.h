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


char* serialize_smartcard_status(int * buf_len);

void deserialize_smartcard_status(const char * ascii, int length);

char* serialize_APDU_response(int * buf_len);

void deserialize_APDU_command(const char * ascii, int length);




#ifdef __cplusplus
}
#endif

#endif //__SERIALIZE_UTIL_H