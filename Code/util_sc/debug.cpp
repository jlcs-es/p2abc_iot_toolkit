#include "debug.h"
#include <iostream>
#include <iomanip>

using namespace std;

void imprimirHexadecimal(BYTE *buffer, int length){
    for (int i = 0; i < length; i++) {
        cout << hex << setfill('0') << setw(2) << (unsigned)buffer[i] ;
    }
    cout << endl;
}
