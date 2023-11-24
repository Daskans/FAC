CFLAGS = -Wall -Wextra -g -std=c99
LDFLAGS = -lm

ALL: test colors

test: test.o
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

colors: colors.o
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

colors.o: colors.c

test.o: test.c
	$(CC) $(CFLAGS) $< -c

clean:
	rm -f *.o test colors