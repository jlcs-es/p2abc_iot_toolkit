

/********************************************************************/
/******************************* BIOSC ******************************/
/********************************************************************/

/********************************************************************/
/**                   Basic Input Output SmartCard                  */
/** Simple main function to generate a standalone binary to run the */
/* Toolkit using files as I/O.                                      */
/********************************************************************/


#include <smartcard_utils_interface/sc_status_io_util.h>
#include <smartcard_common/APDU_handler.h>
#include <smartcard_common/global_vars.h>
#include <smartcard_utils_interface/serialize_util.h>
#include <stdio.h>
#include <stdlib.h>


void receive_commands(){
/*
 * Read from standard input a byte for the operation:
 *  - 0x01 : APDU received.
 *          Read a WORD for APDU length and then as many bytes as said length.
 *  - 0xff : Connection closed.
 *          Finish the loop.
 */

    // TODO : ahora se lee en formato AA cada byte. Cambiar a bytes.

    BYTE command = 0x00;
    WORD apdu_len;
    BYTE apdu_bytes[MAX_APDU_INPUT_DATA_SIZE];
    while(command != 0xff){
        scanf("%2hhx", &command);
        if(command == 0x01){    // 0x01 : APDU received
            // Read APDU Length
            scanf("%4hx", &apdu_len);
            // Read APDU
            for(int i=0; i<apdu_len; i++){
                scanf("%2hhx", &apdu_bytes[i]);
                //scanf("%c", &apdu_bytes[i]);
            }
            // Interpret the bytes
            deserialize_APDU_command(apdu_bytes, apdu_len);
            // Handle the APDU Command
            handle_APDU();
        }
    }
}

void test_JSON1(){
    mode = MODE_ROOT;
    pin[0] = 0x01; pin[1] = 0x23; pin[2] = 0x45; pin[3] = 0xAB;
    pin_trials = 0x12;
    x_size = 0xABCD;
    credentials[0].credential_id = 0x01;
    credentials[1].credential_id = 0x02;
    credentials[2].credential_id = 0x03;
    auth_keys[0][2] = 0x62;
    auth_keys[1][1] = 0x21;

    char * json_string = serialize_smartcard_status();
    FILE * f = fopen( "./status.json", "w+");
    if(f==NULL) exit -1;
    fputs(json_string, f);
    free(json_string);
    fclose(f);
}


int main(int argc, char **argv){

//    if (argc < 2) {
//        printf("Usage: %s smartcard_status_file", argv[0]);
//        return -1;
//    }

    test_JSON1();

    // Restore the smartcard environment
    json_file = "./status.json";
    init_smartcard_from_json_file(json_file);

    // Loop listening for APDUs
    receive_commands();

    return 0;

}


// TODO :
//      * Check if there exists "reset" command, meaning that the Commmand-Response Dialogue is finished and it's like
//        unplugging and plugging the smartcard.