
#ifndef JOY_H
#define JOY_H JOY_H

/* read and write is from the atari's point of view, so reversed in atmel */
struct joy_s
{
   unsigned char port;
   unsigned char data;
   unsigned char lrclk;
   unsigned char lwclk;
   unsigned char queue;
   unsigned char rclk;
   unsigned char rdata;
   unsigned char wclk;
   unsigned char wdata;
};

typedef struct joy_s joy_t;

void joy_setup( joy_t *joy,
                unsigned char port, unsigned char queue_mask,
                unsigned char rdata_mask, unsigned char rclk_mask, 
                unsigned char wdata_mask, unsigned char wclk_mask );

unsigned char joy_get_clocks( joy_t *joy );
unsigned char joy_get_input( joy_t *joy );
void joy_set_output( joy_t *joy, unsigned char data, unsigned char available );

#endif
