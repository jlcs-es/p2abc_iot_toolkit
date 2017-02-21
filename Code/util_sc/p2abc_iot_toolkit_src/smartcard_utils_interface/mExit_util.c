#include <smartcard_utils_interface/mExit_util.h>
#include <smartcard_utils_interface/serialize_util.h>
#include <smartcard_common/defs_types.h>
#include <smartcard_utils_interface/sc_status_io_util.h>
///////////////////////////////////////////////////////////////////////

/********************************************************************/
/*   Implementation that prints to Standard Output the APDU bytes   */
/*   and delegates to sc_status_io to save the sc status to         */
/*   the same json file from start                                  */
/********************************************************************/
#include <smartcard_common/APDU_types.h>
#include <smartcard_common/global_vars.h>
#include <stdio.h>

void output_apdu_response(){
    for(i=0; i<La; ++i)     // data
        printf("%02X", apdu_data.dataout[i]);
    printf("%02X%02X", SW1, SW2);   // SW
}

void save_status(){
    save_smartcard_to_json_file(json_file);
}