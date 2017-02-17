#include <smartcard_utils_interface/output_APDU_response.h>
#include <smartcard_utils_interface/serialize_util.h>
#include <smartcard_common/defs_types.h>
#include <debug.h>


/********************************************************************/
/*   Implementation that prints to Standard Output the APDU bytes   */
/********************************************************************/

void output_apdu_response(){
    int size;
    BYTE * ap_r =  serialize_APDU_response(&size);

    imprimirHexadecimal(ap_r, size);

}

