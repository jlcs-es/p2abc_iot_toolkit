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
#include <debug.h>
#include <malloc.h>
#include <smartcard_common/APDU_types.h>

void output_apdu_response(){
    int size;
    BYTE ap_r[MAX_APDU_OUTPUT_DATA_SIZE];
    serialize_APDU_response(ap_r, &size);
    imprimirHexadecimal(ap_r, size);
}

void save_status(){
    save_smartcard_to_json_file(json_file);
}