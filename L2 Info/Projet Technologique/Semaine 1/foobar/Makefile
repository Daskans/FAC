CC = gcc
AR = ar
CFLAGS = -Wall -std=c99
LDFLAGS = -L.
LDLIBS = -lm

ALL: solve convert

libtsp.a: matrice2d.o memoire.o tsp.o
	$(AR) rcs $@ $^

solve: solve.o libtsp.a
	$(CC) $^ $(LDLIBS) -o $@ 

convert: convert.o libtsp.a
	$(CC) $^ $(LDLIBS) -o $@


solve.o: solve.c tsp.h matrice2d.h
	$(CC) $< -c 

convert.o: convert.c tsp.h matrice2d.h
	$(CC) $< -c 

matrice2d.o: matrice2d.c matrice2d.h memoire.h
	$(CC) $< -c 

memoire.o: memoire.c memoire.h
	$(CC) $< -c 

tsp.o: tsp.c tsp.h matrice2d.h memoire.h
	$(CC) $< -c 

clean:
	rm -f *.a *.o convert solve

.PHONY: ALL clean