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
