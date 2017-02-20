#ifndef __SC_STATUS_IO_UTIL_H
#define __SC_STATUS_IO_UTIL_H

#ifdef __cplusplus
extern "C" {
#endif


/********************************************************************/
/************************ SC STATUS IO UTIL *************************/
/********************************************************************/

/********************************************************************/
/** Initializes the static data of the smartcard.                   */
/********************************************************************/
/** THIS INTERFACE MAY BE CHANGED FOR TARGET PLATFORM               */
/** AND INITIALIZATION/STORING METHOD                               */
/********************************************************************/

// Using Json Files
char * json_file;
void init_smartcard_from_json_file(char * smartcard_status_file);
void save_smartcard_to_json_file(char * json_file);


#ifdef __cplusplus
}
#endif

#endif //__SC_STATUS_IO_UTIL_H