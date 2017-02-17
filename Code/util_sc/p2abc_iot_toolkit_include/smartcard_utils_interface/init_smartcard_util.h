#ifndef __INIT_SMARTCARD_UTIL_H
#define __INIT_SMARTCARD_UTIL_H

#ifdef __cplusplus
extern "C" {
#endif


/********************************************************************/
/*********************** INIT SMARTCARD UTIL ************************/
/********************************************************************/

/********************************************************************/
/** Initializes the static data and I/O of the smartcard.           */
/********************************************************************/
/** THIS INTERFACE MAY BE CHANGED FOR TARGET PLATFORM               */
/** ONLY INTERFACE TO BE CALLED FROM OUTSIDE THE SMARTCARD CORE     */
/** MODIFY AS YOU NEED, THE CORE WILL NOT USE IT.                   */
/********************************************************************/




void init_smartcard_from_file(char * smartcard_status_file);

void init_smartcard_for_tests(); // uses stdout and test files



#ifdef __cplusplus
}
#endif

#endif //__INIT_SMARTCARD_UTIL_H