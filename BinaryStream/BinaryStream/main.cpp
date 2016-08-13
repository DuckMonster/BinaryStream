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

	str.write<int>( 50 );
	str.write<char[7]>( "Hello!" );
	str.write( A( ) );

	cout << str.read<int>( );
	cout << ", ";
	
	for (int i=0; i < 7; i++)
		cout << str.read<char>( );

	A foo = str.read<A>( );

	cout << ", " << foo.a << ":" << foo.b;

	return 0;
}