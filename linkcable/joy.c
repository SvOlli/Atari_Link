
#include "joy.h"
#include "serial.h"

#include <avr/io.h>
#include <util/delay.h>

void joy_setup( joy_t *joy,
                unsigned char port, unsigned char queue_mask,
                unsigned char rdata_mask, unsigned char rclk_mask,
                unsigned char wdata_mask, unsigned char wclk_mask )
{
   switch( port )
   {
   case 'B':
      DDRB &= ~( wclk_mask  | wdata_mask | rclk_mask );
      DDRB |=  ( queue_mask | rdata_mask );
      joy->data = PINB & ( wclk_mask  | wdata_mask | rclk_mask );
      break;
   case 'D':
      DDRD &= ~( wclk_mask  | wdata_mask | rclk_mask );
      DDRD |=  ( queue_mask | rdata_mask );
      joy->data = PIND & ( wclk_mask  | wdata_mask | rclk_mask );
      break;
   default:
      break;
   }
   
#if 0
   serial_string( "\nqum:" );
   serial_hex( queue_mask );
   serial_string( "\nrdm:" );
   serial_hex( rdata_mask );
   serial_string( "\nrcm:" );
   serial_hex( rclk_mask );
   serial_string( "\nwdm:" );
   serial_hex( wdata_mask );
   serial_string( "\nwcm:" );
   serial_hex( wclk_mask );
   serial_byte( '\n' );
#endif
   
   joy->port  = port;
   joy->lrclk = joy->data & rclk_mask;
   joy->lwclk = joy->data & wclk_mask;
   joy->queue = queue_mask;
   joy->rclk  = rclk_mask;
   joy->rdata = rdata_mask;
   joy->wclk  = wclk_mask;
   joy->wdata = wdata_mask;
}


unsigned char joy_get_clocks( joy_t *joy )
{
   unsigned char changed = 0;
   unsigned char counter = 0;
   unsigned char last = 0;
   unsigned char data = 0;
   unsigned char mask = joy->rclk | joy->wclk | joy->wdata;

   for( counter = 0; counter < 5; counter++ )
   {
      last = data;
      switch( joy->port )
      {
      case 'B':
         data = PINB & mask;
         break;
      case 'D':
         data = PIND & mask;
         break;
      default:
         break;
      }
      if( data != last )
      {
         counter = 0;
      }
   }
   if( (data & joy->rclk) != (joy->data & joy->rclk) )
   {
      changed |= joy->rclk;
   }
   if( (data & joy->wclk) != (joy->data & joy->wclk) )
   {
      changed |= joy->wclk;
   }

   joy->data = data;

   return changed;
}


unsigned char joy_get_input( joy_t *joy )
{
   return (joy->data & joy->wdata) ? 1 : 0;
}


void joy_set_output( joy_t *joy, unsigned char data, unsigned char available )
{
   if( data )
   {
      joy->data |= joy->rdata;
   }
   else
   {
      joy->data &= ~(joy->rdata);
   }
   
   /* button = 0 (pressed): data available */
   if( available )
   {
      joy->data &= ~(joy->queue);
   }
   else
   {
      joy->data |= joy->queue;
   }

   switch( joy->port )
   {
   case 'B':
      PORTB = joy->data;
      break;
   case 'D':
      PORTD = joy->data;
      break;
   default:
      break;
   }
}
