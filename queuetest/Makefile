
PROG = queuetest
OBJS = queuetest.o queue.o
CC=gcc
CFLAGS += -g -I../linkcable -Wall -pedantic

all: $(PROG)

$(PROG): $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

%.o: ../linkcable/%.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean realclean:
	rm -f $(OBJS) $(PROG)

