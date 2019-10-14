
#include <queue.h>

#include <stdio.h>


void dump_queue( char c, queue_t *queue )
{
   unsigned char p = queue->inpos;
   unsigned char a = queue->available;
   printf("%c:%02x:", c, queue->available);
   while( a )
   {
      putchar( queue->buffer[p] );
      if( (++(p)) >= QUEUE_SIZE )
      {
         p = 0;
      }
      a--;
   }
   putchar('\n');
}


int main()
{
   int i;
   queue_t queue_a_to_b;
   queue_t queue_b_to_a;
   queue_setup( &queue_a_to_b );
   queue_setup( &queue_b_to_a );
   
   while( (i = getchar()) != EOF )
   {
      switch(i)
      {
         case 'A':
            while( (i = getchar()) != '\n' )
            {
               queue_append( &queue_a_to_b, i );
            }
            break;
         case 'B':
            while( (i = getchar()) != '\n' )
            {
               queue_append( &queue_b_to_a, i );
            }
            break;
         case 'a':
            if( queue_b_to_a.available )
            {
               printf( "pulling:%c\n", queue_head( &queue_b_to_a ) );
               queue_drop( &queue_b_to_a );
            }
            break;
         case 'b':
            if( queue_a_to_b.available )
            {
               printf( "pulling:%c\n", queue_head( &queue_a_to_b ) );
               queue_drop( &queue_a_to_b );
            }
            break;
         case 'd':
         case 'D':
            dump_queue( 'A', &queue_b_to_a );
            dump_queue( 'B', &queue_a_to_b );
            break;
      }
   }      
   
   return 0;
}
