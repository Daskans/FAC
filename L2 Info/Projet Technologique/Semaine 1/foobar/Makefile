CFLAGS = -Wall -std=c99
LDLIBS = -lm

ALL: foobar

libfb.a: foo.o bar.o
	$(AR) rcs $@ $^

foobar: foobar.o libfb.a
	$(CC) $^ $(LDLIBS) -o $@ 

foobar.o: foobar.c libfb.a
	$(CC) $< $(LDLIBS) -c

foo.o: foo.c foo.h
	$(CC) $< -c 

bar.o: bar.c bar.h
	$(CC) $< -c 

clean:
	rm -f *.a *.o foobar

.PHONY: ALL clean