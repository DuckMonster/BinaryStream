# BinaryStream
A binary stream class for C++, for parsing generic types out of a binary stream of data.

##Usage
```
// Creating the stream
bstream str;

int a = 500;
str << a; // Writing int onto stream ( converting it to 4 bytes and saving it in the buffer )

int b;
str >> b; // Reading int from stream ( reading the first 4 bytes in buffer and converting them to an int )
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
