#include <smartcard_utils_interface/mExit_util.h>
///////////////////////////////////////////////////////////////////////
/********************************************************************/

/*   Implementation that writes to connfd the APDU bytes            */
/*   and delegates to sc_status_io to save the sc status to         */
/*   the same json file from start                                  */
/********************************************************************/
#include <smartcard_common/defs_types.h>
#include <smartcard_utils_interface/sc_status_io_util.h>
#include <smartcard_common/APDU_types.h>
#include <smartcard_common/global_vars.h>
#include <unistd.h>

void output_apdu_response(){
    WORD APDUlength = La + 2;
    write(connfd, &APDUlength, 2);
    write(connfd, apdu_data.dataout, La);
    write(connfd, &SW1, 1);
    write(connfd, &SW2, 1);
    fsync(connfd);
}

void save_status(){
    save_smartcard_to_json_file(json_file);
}