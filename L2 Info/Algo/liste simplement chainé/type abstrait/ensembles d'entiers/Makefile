CFLAGS = -Wall -Wextra -g -std=c99
LDFLAGS = -lm

ALL: intset

intset: intset.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

intset.o: intset.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f *.o intset