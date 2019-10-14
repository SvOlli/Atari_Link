#include <avr/io.h>
#include <util/delay.h>

static char lpd = 0;

void serial_init(unsigned int baud)
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


void serial_string(char *c)
{
   while(*c)
   {
      while ( !(UCSR0A & (1 << UDRE0)) )
         ;
      UDR0 = *(c++);
   }
}


void serial_byte(unsigned char c)
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


void setbit( unsigned char bit, unsigned char on )
{
   unsigned char mask = 0;
   
   if( bit > 13 )
   {
      return;
   }
   if( bit > 7 )
   {
      mask = 1 << (bit - 8);
      serial_string( "\nport B: mask " );
      DDRB |= mask;
      if( on )
      {
         serial_hex( mask );
         PORTB |= mask;
      }
      else
      {
         serial_hex( ~mask );
         PORTB &= ~mask;
      }
   }
   else
   {
      mask = 1 << bit;
      serial_string( "\nport D: mask " );
      DDRD |= mask;
      if( on )
      {
         serial_hex( mask );
         PORTD |= mask;
      }
      else
      {
         serial_hex( ~mask );
         PORTD &= ~mask;
      }
   }
}


int main()
{
   unsigned char b;
   serial_string( "A-N: set bit 0-13\n"
                  "a-n: set bit 0-13\n" );
   for(;;)
   {
      b = serial_read();
      if( b )
      {
         if( b == 'x' )
         {
            for( b = 0; b < 14; b++ )
            {
               setbit( b, 0 );
            }
            b = 0;
         }
         if( b == 'X' )
         {
            for( b = 0; b < 14; b++ )
            {
               setbit( b, 1 );
            }
            b = 0;
         }
         if( (b >= 'a') && (b <= 'n') )
         {
            setbit( b - 'a', 0 );
         }
         if( (b >= 'A') && (b <= 'N') )
         {
            setbit( b - 'A', 1 );
         }
         serial_byte( b );
      }
   }
   
   return 1;
}
