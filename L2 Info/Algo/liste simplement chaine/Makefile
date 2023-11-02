CFLAGS = -Wall -Wextra -g
CPPFLAGS = -I.
LDFLAGS = 

all: slist_tests

slist_tests: slist_tests.o slist.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

slist_tests.o: slist_tests.c slist.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $<

slist.o: slist.c slist.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $<

clean:
	rm -f slist_tests *.o

.PHONY: all clean
