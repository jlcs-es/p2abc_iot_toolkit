#include <iostream>
#include <defs_types.h>
#include <crypto_help.h>
#include <iomanip>


using namespace std;


void testRandom8Bytes(){
    cout << "·\ttestRandom8Bytes" << endl << endl;

    BYTE buffer[8];

    for (int i = 0; i < 8; i++) {
        buffer[i] = 0xff;
        cout << hex << setfill('0') << setw(2) << (int)buffer[i] << " ";
    }
    cout << endl;

    mGetRandomNumber(buffer);

    for (int i = 0; i < 8; i++) {
        cout << hex << setfill('0') << setw(2) << (int)buffer[i] << " ";
    }
    cout << endl;

    mGetRandomNumber(buffer);

    for (int i = 0; i < 8; i++) {
        cout << hex << setfill('0') << setw(2) << (int)buffer[i] << " ";
    }
    cout << endl;


}

int main() {
    cout << "Hello, World!" << endl;

    testRandom8Bytes();

    return 0;
}
