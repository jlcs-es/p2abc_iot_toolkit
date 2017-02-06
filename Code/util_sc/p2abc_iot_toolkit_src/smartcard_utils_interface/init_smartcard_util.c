#include <smartcard_utils_interface/init_smartcard_util.h>
#include <smartcard_utils_interface/serialize_util.h>
#include <stdio.h>
#include <stdlib.h>
#include <smartcard_utils_interface/error_codes.h>


void manage_smartcard_status_file(char * smartcard_status_file){
    // 1. Open smartcard file
    FILE * f = fopen( "./status.json", "rb");
    if(f==NULL) exit(ERROR_CANT_OPEN_FILE);
    // 2. Save to array of char
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);  //same as rewind(f);
    char * string = (char*)malloc(fsize + 1);
    if(string==NULL) exit(ERROR_CANT_MALLOC);
    if(fread(string, 1, fsize, f) < fsize) exit(ERROR_CANT_READ_FILE);
    string[fsize] = 0;
    // 3. Close smartcard file
    fclose(f);
    // 4. Call serialize_util.h deserialize_smartcart_status
    deserialize_smartcard_status(string);
    // 5. Free allocated string
    free(string);
    // TODO ~ Save filename for mExit
}

void manage_APDU_command_file(char * APDU_command_file) {
    // 1. Open apdu file
    // 2. Save to array of char
    // 3. Call serialize_util.h deserialize_apdu_command
    // 4. Close apdu file
}

void manage_APDU_response_file(char * APDU_response_file) {
    // ~ save file name for exit save
}

void init_smartcard_with_files(char * smartcard_status_file, char * APDU_command_file, char * APDU_response_file){
    manage_smartcard_status_file(smartcard_status_file);
    manage_APDU_command_file(APDU_command_file);
    manage_APDU_response_file(APDU_response_file);
    // TODO decidir dónde guardar el response file. Idea: que init_smartcard también sea el que se llama al salir desde mExit ¿o desde el BIOSC?, y lo mismo que se encarga de deserializar, serializará el status y response file.
}

void init_smartcard_for_tests(){
    // NOT IMPLEMENTED
}

