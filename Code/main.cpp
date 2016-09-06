#include <iostream>
#include <defs_types.h>
#include <m_adapted_API.h>
#include <iomanip>
#include <subroutines.h>
#include <crypto_util.h>

using namespace std;


void imprimirHexadecimal(BYTE *buffer, int length){
    for (int i = 0; i < length; i++) {
        cout << "0x" << hex << setfill('0') << setw(2) << (unsigned)buffer[i] << ", ";
    }
    cout << endl;
}

void testRandom8Bytes(){
    cout << "·\ttestRandom8Bytes" << endl << endl;

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





int main() {
    cout << "Hello, World!" << endl;

    cout << "BYTE: " << sizeof(BYTE) << " - SBYTE: "<< sizeof(SBYTE)<< endl;
    cout << "WORD: " << sizeof(WORD) << " - SWORD: " << sizeof(SWORD)  << endl;
    cout << "DWORD: "<< sizeof(DWORD) << " - SDWORD: " << sizeof(SDWORD) << endl;


    return 0;
}
