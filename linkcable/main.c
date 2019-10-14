
#include "serial.h"
#include "joy.h"
#include "queue.h"

#include <avr/io.h>
#include <util/delay.h>

int main()
{
   const char message[] = "\nAtari 2600 VCS Link Cable by (c) 2012 SvOlli\n";
   unsigned char clockmask;
   unsigned char data;
   unsigned short i;
   joy_t joy_D;
   joy_t joy_B;
   queue_t queue_D2B;
   queue_t queue_B2D;

   serial_init(57600);
   serial_string(message);

   /* setup led */
   DDRB = 0x20; /* set D13 (LED) for output, set D12 to  */
   DDRD = 0x80; /* set D7 for output as additional GND */
   PORTB = 0x00;
   PORTD = 0x00;

   /* bitmasks are:      queue  rdat  rclk  wdat  wclk */
   joy_setup( &joy_D, 'D', 1<<2, 1<<6, 1<<5, 1<<4, 1<<3 );
   joy_setup( &joy_B, 'B', 1<<0, 1<<4, 1<<3, 1<<2, 1<<1 );
   queue_setup( &queue_D2B );
   queue_setup( &queue_B2D );

   for(;;)
   {
      if( queue_B2D.available || queue_D2B.available )
      {
         PORTB &= ~0x20;
      }
      else
      {
         PORTB |= 0x20;
      }
      
      joy_set_output( &joy_B, queue_head( &queue_B2D ), queue_B2D.available );
      clockmask = joy_get_clocks( &joy_D );
      if( clockmask & joy_D.rclk )
      {
         /* handle data read */
         if( queue_B2D.available )
         {
            serial_byte( queue_head( &queue_B2D ) ? 'I' : 'i' );
            queue_drop( &queue_B2D );
         }
      }
      if( clockmask & joy_D.wclk )
      {
         /* handle data write */
         data = joy_get_input( &joy_D );
         queue_append( &queue_D2B, data );
         serial_byte( data ? 'O' : 'o' );
      }

      joy_set_output( &joy_B, queue_head( &queue_D2B ), queue_D2B.available );
      clockmask = joy_get_clocks( &joy_B );
      if( clockmask & joy_B.rclk )
      {
         /* handle data read */
         if( queue_D2B.available )
         {
            serial_byte( queue_head( &queue_D2B ) ? 'R' : 'r' );
            queue_drop( &queue_D2B );
         }
      }
      if( clockmask & joy_B.wclk )
      {
         /* handle data write */
         data = joy_get_input( &joy_B );
         queue_append( &queue_B2D, data );
         serial_byte( data ? 'W' : 'w' );
      }
   }
   
   return 1;
}
