#ifndef __MEXIT_UTILH
#define __MEXIT_UTILH

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************/
/*************************** mExit Util  ****************************/
/********************************************************************/




void save_status();


/**
 * Takes the values in the APDU variables and public data
 * and outputs it as APDU response.
 */
void output_apdu_response();



#ifdef __cplusplus
}
#endif

#endif //__MEXIT_UTIL_H