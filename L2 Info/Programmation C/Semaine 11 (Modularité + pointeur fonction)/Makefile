CFLAGS = -Wall -std=c99
LDLIBS = -lm

ALL: matrix

matrix: main.o matrice.o
	$(CC) $(CFLAGS) $^ -o $@

main.o: main.c matrice.h
	$(CC) $(CFLAGS) $< -c $@

matrice.o: matrice.c matrice.h
	$(CC) $(CFLAGS) $< -c $@

clean:
	rm -f *.o *.gch matrix

.PHONY: ALL clean