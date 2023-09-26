AR = ar
CFLAGS = -Wall -Wextra -g -std=c99
LDFLAGS = -lm

ALL: complex

complex: complex.o complex.h
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

complex.o: complex.c complex.h
	$(CC) $(CFLAGS) $< -c

clean:
	rm -f *.o complex