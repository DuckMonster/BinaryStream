#include "CppUnitTest.h"
#include "../BinaryStream/bstream.hpp"
#include <functional>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

struct Foo {
public:
    int a;
    double b;
    char c;

    Foo( ) { a = 0; b = 0; c = 0; }
    Foo( int a, double b, char c ) { this->a = a; this->b = b; this->c = c; }
};

TEST_CLASS( BstreamTest ) {
public:

    TEST_METHOD( Initalization ) {
        bstream str;

        {   // New bstream size
            Assert::AreEqual<unsigned int>( 0, str.size( ), L"Size is not 0" );
            Assert::AreEqual<unsigned int>( 0, str.getCursor( ), L"Cursor is not at 0" );
        }
    }

    TEST_METHOD( SingleInteger ) {   // Add integer
        bstream str;

        int i = 257;
        str << i;

        // Check size
        Assert::AreEqual<unsigned int>( str.size( ), 4, L"bstream size is not 4 after writing" );

        // Check buffer content
        const byte* ptr = str.begin( );

        if (ptr[0] != 1 || ptr[1] != 1 || ptr[2] != 0 || ptr[3] != 0)
            Assert::Fail( L"bstream content is not representative of int=257" );
    }

    TEST_METHOD( IntDoubleStruct ) {
        bstream str;

        // Some variables
        int i = 521300;
        double d = 9023.155220;
        Foo foo( 52, 0.525150, 'D' );

        // Write into stream
        str << i << d << foo;

        // New variables
        int i2;
        double d2;
        Foo foo2;

        // Read from stream
        str >> i2 >> d2 >> foo2;

        Assert::AreEqual( i, i2, L"Integers are not equal" );
        Assert::AreEqual( d, d2, L"Doubles are not equal" );
        Assert::IsTrue( memcmp( &foo, &foo2, sizeof( Foo ) ) == 0, L"Structs are not equal" );

        Assert::ExpectException<std::exception>( [=] { str.peek<Foo>(); }, L"No exception thrown when reading beyond buffer" );

        // Do some clear checking
        str.clear( );
        Assert::AreEqual<unsigned int>( 0, str.size( ), L"Size is not 0 after clear" );
        Assert::AreEqual<unsigned int>( 0, str.getCursor( ), L"Cursor position is not 0 after clear" );
    }

    TEST_METHOD( CursorPositions ) {
        bstream str;

        int i = 0;
        str << i;

        for (size_t i = 0; i <= str.size( ); i++)
            str.setCursor( i );

        // Beyond size, exception
        Assert::ExpectException<std::exception>( [&str] { str.setCursor( 5 ); }, L"No exception thrown when setting cursor to more than size (4)" );

        str << i;

        str.setCursor( 5 );

        for (size_t i = 0; i <= str.size( ); i++)
            str.setCursor( i );

        Assert::ExpectException<std::exception>( [&str] {str.setCursor( 9 ); }, L"No exception thrown when setting cursor to more than size (8)" );
    }
};