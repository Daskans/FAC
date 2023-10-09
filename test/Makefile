CFLAGS = -Wall -Wextra -g -std=c99
LDFLAGS = -lm

ALL: test

test: test.o
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

test.o: test.c
	$(CC) $(CFLAGS) $< -c

clean:
	rm -f *.o test