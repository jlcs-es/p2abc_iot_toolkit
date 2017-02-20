#include <smartcard_utils_interface/sc_status_io_util.h>
#include <smartcard_utils_interface/serialize_util.h>
#include <stdio.h>
#include <stdlib.h>
#include <smartcard_utils_interface/error_codes.h>


void init_smartcard_from_json_file(char * json_file){
    // 1. Open smartcard file
    FILE * f = fopen(json_file, "rb");
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

void save_smartcard_to_json_file(char * json_file){
    //TODO save write
    // 1. Open smartcard file
    FILE * f = fopen(json_file, "w+");
    if(f==NULL) exit(ERROR_CANT_OPEN_FILE);
    // 2. Save to array of char
    char * json_string = serialize_smartcard_status();
    if(json_string==NULL) exit(ERROR_CANT_MALLOC);
    fputs(json_string, f);
    // 3. Close smartcard file
    fclose(f);
    // 4. Free allocated string
    free(json_string);
}
