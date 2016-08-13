#pragma once
#include <vector>

typedef unsigned char byte;

class bstream {
public:
	bstream( ) { };

	template<typename T>
	void					write( const T& value );

	template<typename T>
	T						read( );

private:
	std::vector<byte>		buffer;
	size_t					cursor	= 0;
};

template<typename T>
inline void bstream::write( const T& value ) {
	// Create a pointer to memory
	const void*	ptr		= &value;

	// Go through this pointer and adding each byte value to buffer
	for (int i=0; i < sizeof( T ); i++) {
		// Convert void* to byte*, then tranverse the pointer i steps and get the value
		buffer.push_back( *(((byte*)ptr) + i) );
	}
}

template<typename T>
inline T bstream::read( ) {
	// Pointer to memory
	void*	ptr = &buffer[cursor];

	// Convert to T*
	T*		tPtr = (T*)ptr;

	// Advance cursor
	cursor += sizeof( T );

	// Return value at adress
	return *tPtr;
}