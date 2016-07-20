#include <iostream>
#include <defs_types.h>
#include <m_adapted_API.h>
#include <iomanip>
#include <subroutines.h>

using namespace std;


void testRandom8Bytes(){
    cout << "·\ttestRandom8Bytes" << endl << endl;

    BYTE buffer[8];

    for (int i = 0; i < 8; i++) {
        buffer[i] = 0xff;
        cout << hex << setfill('0') << setw(2) << (unsigned)buffer[i] << " ";
    }
    cout << endl;

    mGetRandomNumber(buffer);

    for (int i = 0; i < 8; i++) {
        cout << hex << setfill('0') << setw(2) << (unsigned)buffer[i] << " ";
    }
    cout << endl;

    mGetRandomNumber(buffer);

    for (int i = 0; i < 8; i++) {
        cout << hex << setfill('0') << setw(2) << (unsigned)buffer[i] << " ";
    }
    cout << endl;


}

void testRandom85Bytes(){
    BYTE buffer[85];
    for (int i = 0; i < 85; i++) {
        buffer[i] = 0xff;
    }
    getRandomBytes(buffer, 85);

    for (int i = 0; i < 85; i++) {
        cout << "0x" << hex << setfill('0') << setw(2) << (unsigned)buffer[i] << ", ";
    }
}

int main() {
    cout << "Hello, World!" << endl;

    //testRandom8Bytes();
    testRandom85Bytes();

    return 0;
}
