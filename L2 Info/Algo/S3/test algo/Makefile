CC = gcc
AR = ar
CFLAGS = -Wall -std=c99

ALL: hanoi_test

hanoi_test: hanoi_test.c hanoi.c hanoi.h
	$(CC) $(CFLAGS) $< -o $@

hanoi_test.o: hanoi_test.c hanoi.h
	$(CC) $< -c

hanoi.o: hanoi.c hanoi.h
	$(CC) $< -c

clean:
	rm -f *.o hanoi_test