#ifndef __SERIALIZE_STATIC_DATA_H
#define __SERIALIZE_STATIC_DATA_H

#ifdef __cplusplus
extern "C" {
#endif


/********************************************************************/
/********************** SERIALIZE STATIC DATA ***********************/
/********************************************************************/

/********************************************************************/
/** Function to serialize/deserialize the static memory, variables  */
/* that must persist from one execution to another.                 */
/********************************************************************/
/** This file resides inside the common core because it knows the   */
/* internal structure of the application, what the static data is   */
/* and what structures/types they are. It serializes it to          */
/* arrays of bytes, and will be able to deserialize                 */
/* independently of how they are stored.                            */
/********************************************************************/
/* This functions will call the I/O interface that will store in    */
/* device the serialization. Does not matter if in a file,          */
/* multiple files, registers, a secure memory module, etc.          */
/********************************************************************/


// Functions to serialize all static data from the smartcard

void serialize_static_data();

void deserialize_static_data();



// Functions to serialize different complex data types.

void serialize_BLOB_STORE_ITEM(BYTE* result, WORD* size, const BLOB_STORE_ITEM input);
void serialize_BLOB_CATALOG_STORE_ITEM(BYTE* result, WORD* size, const BLOB_CATALOG_ITEM input);
void serialize_GROUP(BYTE* result, WORD* size, const GROUP input);
#if NUM_COUNTERS > 0
void serialize_COUNTER(BYTE* result, WORD* size, const COUNTER input);
#endif
void serialize_ISSUER(BYTE* result, WORD* size, const ISSUER input);
void serialize_PROVER(BYTE* result, WORD* size, const PROVER input);
void serialize_CREDENTIAL(BYTE* result, WORD* size, const CREDENTIAL input);

//TODO




// Parameters for serialization   (can change between implementations)

#define BLOB_STORE_ITEM_SERIALIZED_BYTES  123
//TODO



/**
 An array is serialized as 0xFF + 2 bytes with the length + the byte array
 A single byte is serialized as 0xEE + byte
 */

#define ARRAY_CODE 0xFF
#define SINGLE_BYTE_CODE 0XEE



#ifdef __cplusplus
}
#endif

#endif //__SERIALIZE_STATIC_DATA_H