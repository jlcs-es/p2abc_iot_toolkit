

/********************************************************************/
/******************************* BIOSC ******************************/
/********************************************************************/

/********************************************************************/
/**                   Basic Input Output SmartCard                  */
/** Simple main function to generate a standalone binary to run the */
/* Toolkit using files as I/O.                                      */
/********************************************************************/


#include <smartcard_utils_interface/init_smartcard_util.h>
#include <smartcard_utils_interface/error_codes.h>
#include <smartcard_common/APDU_handler.h>
#include <smartcard_common/global_vars.h>
#include <smartcard_utils_interface/serialize_util.h>

#include <stdlib.h>
#include <stdio.h>


void receive_commands(){
/*
 * Read from standard input a byte for the operation:
 *  - 0x01 : APDU received.
 *          Read a WORD for APDU length and then as many bytes as said length.
 *  - 0xff : Connection closed.
 *          Finish the loop.
 */

    // TODO : ahora se lee en formato AA cada byte.

    BYTE command = 0x00;
    WORD apdu_len;
    while(command != 0xff){
        scanf("%2hhx", &command);
        if(command == 0x01){    // 0x01 : APDU received
            // Read APDU Length
            scanf("%4hx", &apdu_len);
            // Read APDU
            BYTE * apdu_bytes = malloc(apdu_len);   // TODO Make static using a "free" global var, or use a MAX_APDU_INPUT_DATA_SIZE array
            if(apdu_bytes  == NULL) exit(ERROR_CANT_MALLOC);
            for(i=0; i<apdu_len; i++){
                scanf("%2hhx", &apdu_bytes[i]);
                //scanf("%c", &apdu_bytes[i]);
            }
            // Interpret the bytes
            deserialize_APDU_command(apdu_bytes, apdu_len);
            free(apdu_bytes);
            // Handle the APDU Command
            handle_APDU();
        }
    }
}


int main(int argc, char **argv){

//    if (argc < 2) {
//        printf("Usage: %s smartcard_status_file", argv[0]);
//        return -1;
//    }

    // Restore the smartcard environment
    init_smartcard_from_file("./status.json");

    // Loop listening for APDUs
    receive_commands();

    return 0;

}


// TODO :
//      * Check if there exists "reset" command, meaning that the Commmand-Response Dialogue is finished and it's like
//        unplugging and plugging the smartcard.