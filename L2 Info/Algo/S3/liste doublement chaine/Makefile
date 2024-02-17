CFLAGS = -Wall -Wextra -g
CPPFLAGS = -I.
LDFLAGS = 

all: dlist_tests

dlist_tests: dlist_tests.o dlist.o sort.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

dlist_tests.o: dlist_tests.c dlist.h sort.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $<

dlist.o: dlist.c dlist.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $<

sort.o: sort.c sort.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $<

clean:
	rm -f dlist_tests *.o

.PHONY: all clean
