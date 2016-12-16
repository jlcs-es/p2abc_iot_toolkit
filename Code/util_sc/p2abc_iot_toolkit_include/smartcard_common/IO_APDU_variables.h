#ifndef __IO_APDU_VARIABLES_H
#define __IO_APDU_VARIABLES_H

#ifdef __cplusplus
extern "C" {
#endif


/********************************************************************/
/********************** IO APDU VARIABLES     ***********************/
/********************************************************************/
//todo
/********************************************************************/
/** Manages the global APDU variables to set the values from the    */
/* received APDU and set the values for the APDU response.          */
/********************************************************************/
/** Inherited from multos, the smartcard app starts with the APDU   */
/* data already loaded into the global APDU variables, and exits    */
/* leaving the response data in them. Calling this functions manages*/
/* the variables as multos used to.                                 */
/********************************************************************/
/*      */
/********************************************************************/



/**
 * Initializes the APDU global variables to the values
 * of the received APDU command.
 */
void init_apdu_command();



/**
 * Takes the values in the APDU variables and public data
 * and outputs it as APDU response.
 */
void output_apdu_response();




#ifdef __cplusplus
}
#endif

#endif //__IO_APDU_VARIABLES_H