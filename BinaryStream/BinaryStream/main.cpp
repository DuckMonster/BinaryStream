#include <iostream>
#include <bitset>
#include "bstream.hpp"

using namespace std;

struct A {
    int a = 50;
    int b = 100;
};

int main( ) {
    bstream str;

    int a = 150;
    double d = 120.05;

    str << a << d;
    // Read again

    int a2;
    double d2;

    str >> a2 >> d2;

    cout << a2 << ", " << d2 << "\n";


    const byte*		begin = str.begin( );
    for (int i=0; i < str.size( ); i++) {
        cout << *(begin + i);
    }

    return 0;
}