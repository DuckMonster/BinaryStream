# BinaryStream
A binary stream class for C++, for parsing generic types out of a binary stream of data.

##Usage
###Writing
```
bstream str;

str.write<int>( 250 );  // Write int to stream

int a = 500;
str.write( a );         // Write int to stream

str << a;               // Write int to stream ( using << operator )
```

###Reading
```
bstream str;

int b;

b   = str.peek<int>( );   // Read an int from stream without advancing pointer
b   = str.read<int>( );   // Same, but advancing pointer 4 bytes

str >> b;                 // Same as "b = str.read<int>( )", but using >> operator
```

The << and >> operator can be used multiple times
```
bstream str;

int a = 42;
double d = 3.1415;
char c = 's';

str << a << d << c;     // The stream will output in the same order as it input
str >> a >> d >> c;     //
```

###Examples
```
bstream str;

int i = 50025;
double d = 2553.982;
char c = 's';

str << i << d << c;

cout << str.read<int>( ) << "\n";
cout << str.read<double>( ) << "\n";
cout << str.read<char>( ) << "\n\n";

/*  Outputs:
 *  50025
 *  2553.982
 *  s
 */

str.setCursor( 0 );

int i2;
double d2;
char c2;

str >> i2 >> d2 >> c2;

cout << i2 << "\n" << d2 << "\n" << c2 << "\n\n";

/*  Outputs:
 *  50025
 *  2553.982
 *  s
 */
```
