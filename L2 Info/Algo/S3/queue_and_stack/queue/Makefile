CFLAGS = -Wall -Wextra -g
CPPFLAGS = -I.
LDFLAGS =

all: queue_tests

queue_tests: queue_tests.o queue.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

queue_tests.o: queue_tests.c queue.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $<

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $<

clean:
	rm -f queue_tests *.o

.PHONY: all clean
