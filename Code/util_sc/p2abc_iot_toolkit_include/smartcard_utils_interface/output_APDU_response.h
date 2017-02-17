#ifndef __OUTPUT_APDU_RESPONSE_H
#define __OUTPUT_APDU_RESPONSE_H

#ifdef __cplusplus
extern "C" {
#endif

//TODO renombrar a exit_util
// incluir output APDU response, save sc status, ...

/********************************************************************/
/********************** OUTPUT_APDU_RESPONSE  ***********************/
/********************************************************************/
//todo
/********************************************************************/
/** Manages the global APDU variables to set the values from the    */
/* received APDU and set the values for the APDU response.          */
/********************************************************************/
/********************************************************************/
/*      */
/********************************************************************/


/**
 * Takes the values in the APDU variables and public data
 * and outputs it as APDU response.
 */
void output_apdu_response();




#ifdef __cplusplus
}
#endif

#endif //__OUTPUT_APDU_RESPONSE_H