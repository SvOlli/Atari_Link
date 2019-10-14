
PROG = queuetest
OBJS = queuetest.o queue.o
CC=gcc
CFLAGS += -g -I.. -Wall -pedantic

all: $(PROG)

$(PROG): $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

%.o: ../%.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean realclean:
	rm -f $(OBJS) $(PROG)

