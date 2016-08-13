#include "CppUnitTest.h"
#include "../BinaryStream/bstream.hpp"
#include <functional>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS( BstreamTest ) {
public:

    TEST_METHOD( BasicTest ) {
        bstream str;

        {   // New bstream size
            Assert::AreEqual<unsigned int>( str.size( ), 0, L"New bstream size is not 0" );

            // Exception on getting start with empty stream
            Assert::ExpectException<std::exception>( [=] { throw std::exception( ); }, L"No exception when calling begin() on empty stream" );
        }

        {   // Add integer
            int i = 257;
            str << i;

            // Check size
            Assert::AreEqual<unsigned int>( str.size( ), 4, L"bstream size is not 4 after adding an integer" );

            // Check buffer content
            const byte* ptr = str.begin( );

            if (ptr[0] != 1 || ptr[1] != 1 || ptr[2] != 0 || ptr[3] != 0)
                Assert::Fail( L"bstream content is not representative of int=257" );
        }
    }
};