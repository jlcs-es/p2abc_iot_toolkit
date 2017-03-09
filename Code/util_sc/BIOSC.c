

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
#include <sys/socket.h>
#include <p2abc_iot_toolkit_include/smartcard_utils_interface/error_codes.h>
#include <netinet/in.h>
#include <unistd.h>

void receive_commands(){
/*
 * Read from standard input a byte for the operation:
 *  - 0x01 : APDU received.
 *          Read a WORD for APDU length and then as many bytes as said length.
 *  - 0xff : Connection closed.
 *          Finish the loop.
 */

    BYTE command = 0x00;
    WORD apdu_len;
    BYTE apdu_bytes[MAX_APDU_INPUT_DATA_SIZE];
    while(command != 0xff){
        read(connfd, &command, 1);
        if(command == 0x01){    // 0x01 : APDU received
            // Read APDU Length
            read(connfd, &apdu_len, 2);
            // Read APDU
            read(connfd, apdu_bytes, apdu_len);
            // Interpret the bytes
            deserialize_APDU_command(apdu_bytes, apdu_len);
            // Handle the APDU Command
            handle_APDU();
        }
    }





    // -todoahora se lee en formato AA cada byte. Cambiar a bytes.

//    BYTE command = 0x00;
//    WORD apdu_len;
//    BYTE apdu_bytes[MAX_APDU_INPUT_DATA_SIZE];
//    while(command != 0xff){
//        scanf("%2hhx", &command);
//        if(command == 0x01){    // 0x01 : APDU received
//            // Read APDU Length
//            scanf("%4hx", &apdu_len);
//            // Read APDU
//            for(int i=0; i<apdu_len; i++){
//                scanf("%2hhx", &apdu_bytes[i]);
//                //scanf("%c", &apdu_bytes[i]);
//            }
//            // Interpret the bytes
//            deserialize_APDU_command(apdu_bytes, apdu_len);
//            // Handle the APDU Command
//            handle_APDU();
//        }
//    }
}


int listen_conn(int port) {

    int sockfd, connfd;
    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ){
        exit(ERROR_SOCKET);
    }

    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if( bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 ){
        exit(ERROR_SOCKET);
    }

    if( listen(sockfd, 5) < 0 ){
        exit(ERROR_SOCKET);
    }

    if ( (connfd = accept(sockfd, (struct sockaddr *)NULL, NULL)) < 0 )
        exit(ERROR_SOCKET);

    return connfd;
}






void create_json(){
    mode = MODE_ROOT;

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

    create_json();

    // Restore the smartcard environment
    json_file = "./status.json";
    init_smartcard_from_json_file(json_file);


    // Open socket and listen on port
    connfd = listen_conn(8888);

    // Loop listening for APDUs
    receive_commands();

    close(connfd);

    return 0;

}


// TODO :
//      * Check if there exists "reset" command, meaning that the Commmand-Response Dialogue is finished and it's like
//        unplugging and plugging the smartcard.