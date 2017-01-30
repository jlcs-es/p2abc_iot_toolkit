#include <smartcard_utils_interface/init_smartcard_util.h>

#include <smartcard_utils_interface/serialize_util.h>


void manage_smartcard_status_file(char * smartcard_status_file){
    // 1. Open smartcard file
    // 2. Save to array of char
    // 3. Call serialize_util.h deserialize_smartcart_status
    // 4. Close smartcard file
    // ~ save file name for exit save
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
    // TODO decidir dónde guardar el response file. Idea: que init_smartcard también sea el que se llama al salir, y lo mismo que se encarga de deserializar, serializará el status y response file.
}

void init_smartcard_for_tests(){
    // NOT IMPLEMENTED
}

