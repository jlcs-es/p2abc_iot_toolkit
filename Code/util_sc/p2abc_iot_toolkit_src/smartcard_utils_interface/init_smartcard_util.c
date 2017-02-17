#include <smartcard_utils_interface/init_smartcard_util.h>
#include <smartcard_utils_interface/serialize_util.h>
#include <stdio.h>
#include <stdlib.h>
#include <smartcard_utils_interface/error_codes.h>


char * sc_status_file;

void init_smartcard_from_file(char * smartcard_status_file){
    // ~ Save filename for mExit
    sc_status_file = smartcard_status_file;
    // 1. Open smartcard file
    FILE * f = fopen( sc_status_file, "rb");
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
}

void init_smartcard_for_tests(){
    // NOT IMPLEMENTED
}

