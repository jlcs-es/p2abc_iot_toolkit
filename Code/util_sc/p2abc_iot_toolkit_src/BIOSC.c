

/********************************************************************/
/******************************* BIOSC ******************************/
/********************************************************************/

/********************************************************************/
/**                   Basic Input Output SmartCard                  */
/** Simple main function to generate a standalone binary to run the */
/* Toolkit using files as I/O.                                      */
/********************************************************************/


#include <smartcard_utils_interface/init_smartcard_util.h>
#include <smartcard_common/APDU_handler.h>

#include <stdio.h>



int main(int argc, char **argv){

    if (argc < 4) {
        printf("Usage: %s smartcard_status_file APDU_command_file APDU_response_file", argv[0]);
        return -1;
    }


    init_smartcard_with_files(NULL, NULL, NULL);

    handle_APDU();

    return 0;

}