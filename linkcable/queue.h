
#ifndef QUEUE_H
#define QUENE_H QUENE_H

#define QUEUE_SIZE 128

struct queue_s
{
   unsigned char insize;
   unsigned char outsize;
   unsigned char inpos;
   unsigned char outpos;
   unsigned char available;
   unsigned char buffer[QUEUE_SIZE];
};

typedef struct queue_s queue_t;

void queue_setup( queue_t *queue );

void queue_append( queue_t *queue, unsigned char data );
unsigned char queue_head( queue_t *queue );
void queue_drop( queue_t *queue );

#endif
