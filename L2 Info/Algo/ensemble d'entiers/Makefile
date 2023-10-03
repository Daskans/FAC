CFLAGS = -Wall -std=c99

ALL: intset

intset: inset.o intset.h
	$(CC) $(CFLAGS) $< -o $@

intset.o: intset.c intset.h
	$(CC) $(CFLAGS) $< -c $@

clean:
	rm -f *.o intset