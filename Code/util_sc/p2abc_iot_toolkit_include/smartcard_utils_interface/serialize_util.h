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
/** A function receives an array of BYTES to store as a variable    */
/* serialization. Another function is called when all variables to  */
/* store have been passed.                                          */
/** This lets for storing as the first function is called, or use   */
/* a buffer with special separation between variables, that is      */
/* stored when the second function is called.                       */
/** For reading stored variables, a function is called retrieving   */
/* one serialized array at a time, and a NULL when no more are      */
/* available.                                                       */
/********************************************************************/





#ifdef __cplusplus
}
#endif

#endif //__SERIALIZE_UTIL_H