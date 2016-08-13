#pragma once
#include <vector>

typedef unsigned char byte;

class bstream {
public:
    bstream( ) { };

    // Write value to stream
    template<typename T>
    void                    write( const T& value );

    // Read value from stream and advance cursor
    template<typename T>
    T                       read( );

    // Read value from stream without advancing cursor
    template<typename T>
    T                       peek( ) const;

    // Write operator
    template<typename T>
    bstream&                operator<<( T& value );

    // Read operator
    template<typename T>
    bstream&                operator>>( T& output );

    // Beginning of stream
    const byte*             begin( ) const { if (buffer.size( ) == 0) return nullptr; return &buffer[0]; };
    // Size of stream
    unsigned int            size( ) const { return buffer.size( ); };

    void                    clear( );
    void                    reset( );
    size_t                  getCursor( ) const { return cursor; }
    void                    setCursor( size_t pos );

private:
    std::vector<byte>       buffer;
    size_t                  cursor	= 0;
};

///<summary>Write value onto stream.</summary>
template<typename T>
inline void bstream::write( const T& value ) {
    // Resize the buffer
    buffer.resize( size( ) + sizeof( T ) );

    // Copy memory from parameter onto the end of the buffer
    memcpy( &buffer[size( ) - sizeof( T )], &value, sizeof( T ) );
}

///<summary>Read data from memory and convert it to type T, then advance cursor sizeof(T) bytes.</summary>
template<typename T>
inline T bstream::read( ) {
    // Get value
    T value = peek<T>( );

    // Advance cursor
    cursor += sizeof( T );

    // Return value at adress
    return value;
}

///<summary>Read data from memory and convert it to type T, but don't advance cursor.</summary>
template<typename T>
inline T bstream::peek( ) const {
    // Check if buffer is too small
    if (cursor + sizeof( T ) > size( ))
        throw std::exception( "Tried to read beyond stream size" );

    // Create instance of T
    T       value;

    // Copy memory into value from the buffer
    memcpy( &value, &buffer[cursor], sizeof( T ) );

    return value;
}

///<summary>Write data onto stream.</summary>
template<typename T>
inline bstream& bstream::operator<<( T& value ) {
    // Write into buffer
    write( value );

    // Return reference to self
    return *this;
}

///<summary>Read data from stream, and copy it into <code>output</code>, then advance cursor sizeof(T) bytes.</summary>
template<typename T>
inline bstream & bstream::operator>>( T & output ) {
    // Read value
    T value = read<T>( );

    // Copy memory
    memcpy( &output, &value, sizeof( T ) );

    // Return reference to self
    return *this;
}

///<summary>Clear all data.</summary>
inline void bstream::clear( ) {
    buffer.clear( );
    reset( );
}

///<summary>Reset cursor position to beginning of stream.</summary>
inline void bstream::reset( ) { setCursor( 0 ); }

///<summary>Set cursor to position in stream.</summary>
inline void bstream::setCursor( size_t pos ) {
    if (pos > size( ))
        throw std::exception( "Tried to set cursor position beyond stream size" );

    cursor = pos;
}