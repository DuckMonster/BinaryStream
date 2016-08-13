#pragma once
#include <vector>

typedef unsigned char byte;

class bstream {
public:
    bstream( ) { };

    // Write value to stream
    template<typename T>
    void					write( const T& value );

    // Read value from stream and advance cursor
    template<typename T>
    T                       read( );

    // Read value from stream without advancing cursor
    template<typename T>
    T						peek( );

    // Write operator
    template<typename T>
    bstream&				operator<<( T& value );

    // Read operator
    template<typename T>
    bstream&				operator>>( T& output );

    // Beginning of stream
    const byte*				begin( ) const { return &buffer[0]; };
    // Size of stream
    unsigned int			size( ) const { return buffer.size( ); };

private:
    std::vector<byte>		buffer;
    size_t					cursor	= 0;
};

///<summary>Write value into buffer</summary>
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

///<summary>Read data from memory and convert it to type T, then advance cursor sizeof(T) bytes.</summary>
template<typename T>
inline T bstream::read( ) {
    // Get value
    T		value = peek<T>( );

    // Advance cursor
    cursor += sizeof( T );

    // Return value at adress
    return value;
}

///<summary>Read data from memory and convert it to type T, but don't advance cursor.</summary>
template<typename T>
inline T bstream::peek( ) {
    // Pointer to memory
    void*	ptr = &buffer[cursor];

    // Convert to T*
    T*		tPtr = (T*)ptr;

    // Return value at adress
    return *tPtr;
}

///<summary>Write data into buffer</summary>
template<typename T>
inline bstream& bstream::operator<<( T& value ) {
    // Write into buffer
    write( value );

    // Return reference to self
    return *this;
}

///<summary>Read data from buffer, and copy it into <code>output</code>, then advance cursor sizeof(T) bytes.</summary>
template<typename T>
inline bstream & bstream::operator>>( T & output ) {
    // Read value
    T value = read<T>( );

    // Copy memory
    memcpy( &output, &value, sizeof( T ) );

    // Return reference to self
    return *this;
}
