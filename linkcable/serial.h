
#ifndef SERIAL_H
#define SERIAL_H

void serial_init( unsigned int baud );
void serial_hex( unsigned char byte );
void serial_bin( unsigned char byte );
void serial_string( const char *c );
void serial_byte( unsigned char c );
unsigned char serial_read();

#endif
