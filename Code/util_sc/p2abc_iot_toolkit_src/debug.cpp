#include "debug.h"
#include <iostream>
#include <iomanip>

using namespace std;

void imprimirHexadecimal(BYTE *buffer, int length){
    for (int i = 0; i < length; i++) {
        cerr << hex << setfill('0') << setw(2) << (unsigned)buffer[i] ;
    }
    cerr << endl;
}


void imprimirMensaje(char * msg) {
    cerr << msg << endl;
}