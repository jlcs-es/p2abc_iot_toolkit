#include <iostream>
#include <p2abc_iot_toolkit_include/smartcard_common/defs_types.h>
#include <p2abc_iot_toolkit_include/smartcard_common/m_adapted_API.h>
#include <p2abc_iot_toolkit_include/smartcard_common/subroutines.h>
#include <p2abc_iot_toolkit_include/debug.h>
#include <p2abc_iot_toolkit_include/smartcard_utils_interface/serialize_util.h>
#include <unistd.h>
#include <p2abc_iot_toolkit_include/smartcard_common/global_vars.h>
#include <p2abc_iot_toolkit_include/smartcard_common/APDU_handler.h>
#include <p2abc_iot_toolkit_include/smartcard_common/abc4T_types.h>
#include <iomanip>

using namespace std;


void testRandom8Bytes(){
    cout << "testRandom8Bytes" << endl << endl;

    BYTE buffer[8];
    for (int i = 0; i < 8; i++) {
        buffer[i] = 0xff;
    }

    imprimirHexadecimal(buffer, 8);

    mGetRandomNumber(buffer);

    imprimirHexadecimal(buffer, 8);

    mGetRandomNumber(buffer);

    imprimirHexadecimal(buffer, 8);


}

void testRandom85Bytes(){
    BYTE buffer[85];
    for (int i = 0; i < 85; i++) {
        buffer[i] = 0xff;
    }
    getRandomBytes(buffer, 85);

    imprimirHexadecimal(buffer, 85);
}


void testSizesOfDataTypes() {
    cout << "BYTE: " << sizeof(BYTE) << " - SBYTE: "<< sizeof(SBYTE)<< endl;
    cout << "WORD: " << sizeof(WORD) << " - SWORD: " << sizeof(SWORD)  << endl;
    cout << "DWORD: "<< sizeof(DWORD) << " - SDWORD: " << sizeof(SDWORD) << endl;
}


void test_JSON1(){
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    cout <<  cwd << endl;

    handle_INS_SET_VIRGIN_MODE();
    handle_INS_SET_ROOT_MODE();
    pin[0] = 0x01; pin[1] = 0x23; pin[2] = 0x45; pin[3] = 0xAB;
    pin_trials = 0x12;
    x_size = 0xABCD;
    credentials[0].credential_id = 0x01;
    credentials[1].credential_id = 0x02;
    credentials[2].credential_id = 0x03;
    auth_keys[0][2] = 0x62;
    auth_keys[1][1] = 0x21;
    imprimirHexadecimal(pin, 4);

    char * json_string = serialize_smartcard_status();
    FILE * f = fopen( "./status.json", "w+");
    if(f==NULL) exit -1;
    fputs(json_string, f);
    free(json_string);
    fclose(f);
}



void test_JSON2(){
    handle_INS_SET_VIRGIN_MODE();

    FILE * f = fopen( "./status.json", "rb");
    if(f==NULL) exit -1;
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);  //same as rewind(f);
    char * string = (char*)malloc(fsize + 1);
    if(string==NULL) exit -2;
    if(fread(string, 1, fsize, f) < fsize) exit -3;
    string[fsize] = 0;
    fclose(f);

    deserialize_smartcard_status(string);

    free(string);

    cout << hex << setfill('0') << setw(2) << (unsigned)pin_trials << endl;
    cout << hex << setfill('0') << setw(2) << (unsigned)x_size << endl;
    imprimirHexadecimal(pin, 4);
    cout << hex << setfill('0') << setw(2) << (unsigned)auth_keys[0][2] << endl;
    cout << hex << setfill('0') << setw(2) << (unsigned)auth_keys[1][1] << endl;
}


void test_JSON3() {
    char * json_string = serialize_smartcard_status();
    FILE * f = fopen( "./status2.json", "w+");
    if(f==NULL) exit -1;
    fputs(json_string, f);
    free(json_string);
    fclose(f);
}

int main() {
    cout << "Hello, World!" << endl;
    test_JSON1();
    test_JSON2();
    //test_JSON3();

    return 0;
}
