
#include "serial.h"

#include <avr/io.h>
#include <util/delay.h>


void serial_init( unsigned int baud )
{
   unsigned int bittimer = ( F_CPU / baud / 16 ) - 1;
   /* Set the baud rate */
   UBRR0H = (unsigned char) (bittimer >> 8);
   UBRR0L = (unsigned char) bittimer;
   /* set the framing to 8N1 */
   UCSR0C = (3 << UCSZ00);
   /* Engage! */
   UCSR0B = (1 << RXEN0) | (1 << TXEN0);
}


void serial_hex( unsigned char byte )
{
   unsigned char c;
   c = (byte >> 4);
   serial_byte( c + (( c > 9 ) ?  'W' : '0') );
   c = (byte & 0x0f);
   serial_byte( c + (( c > 9 ) ?  'W' : '0') );
}


void serial_bin( unsigned char byte )
{
   unsigned char c = 0x80;
   while( c )
   {
      serial_byte( byte & c ? '1' : '0' );
      c >>= 1;
   }
}


void serial_string( const char *c )
{
   while(*c)
   {
      while ( !(UCSR0A & (1 << UDRE0)) )
         ;
      UDR0 = *(c++);
   }
}


void serial_byte( unsigned char c )
{
   while ( !(UCSR0A & (1 << UDRE0)) )
      ;
   UDR0 = c;
}


unsigned char serial_read()
{
   if( !(UCSR0A & (1 << RXC0)) )
   {
      return 0;
   }
   return UDR0;
}
