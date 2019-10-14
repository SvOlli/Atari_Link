
#include "queue.h"

#include <stdio.h>

void queue_setup( queue_t *queue )
{
   unsigned char c;
   queue->insize     = QUEUE_SIZE;
   queue->outsize    = QUEUE_SIZE;
   queue->inpos      = 0;
   queue->outpos     = 0;
   queue->available  = 0;
   for( c = 0; c < QUEUE_SIZE; c++ )
   {
      queue->buffer[c] = 0;
   }
}

void queue_append( queue_t *queue, unsigned char data )
{
   if( (++(queue->available)) > QUEUE_SIZE )
   {
      /* call fail routine */
   }
   queue->buffer[queue->outpos] = data;
   if( (++(queue->outpos)) >= QUEUE_SIZE )
   {
      queue->outpos = 0;
   }
}

unsigned char queue_head( queue_t *queue )
{
   return queue->buffer[queue->inpos];
}

void queue_drop( queue_t *queue )
{
   if( !queue->available )
   {
      return;
   }
   --(queue->available);
   if( (++(queue->inpos)) >= QUEUE_SIZE )
   {
      queue->inpos = 0;
   }
}
