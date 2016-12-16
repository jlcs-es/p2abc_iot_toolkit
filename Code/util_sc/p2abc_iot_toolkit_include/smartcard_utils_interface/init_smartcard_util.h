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
/** ONLY INTERFACE THAT MUST BE CHANGED FOR TARGET PLATFORM         */
/** ONLY INTERFACE THAT IS CALLED FROM OUTSIDE THE SMARTCARD CORE   */
/** MODIFY AS YOU NEED, THE CORE WILL NOT USE IT.                   */
/********************************************************************/




void init_smartcard_with_files(char * smartcard_status_file, char * APDU_command_file, char * APDU_response_file);

void init_smartcard_for_tests(); // uses stdout and test files



#ifdef __cplusplus
}
#endif

#endif //__INIT_SMARTCARD_UTIL_H