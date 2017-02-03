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
    credentials[0].credential_id = 0x01;
    credentials[1].credential_id = 0x02;
    credentials[2].credential_id = 0x03;

    int buflen;
    char * json_string = serialize_smartcard_status(&buflen);

    FILE * f = fopen( "./status.json", "w+");
    fputs(json_string, f);

    free(json_string);
    fclose(f);
}


int main() {
    cout << "Hello, World!" << endl;

    test_JSON1();


    return 0;
}
