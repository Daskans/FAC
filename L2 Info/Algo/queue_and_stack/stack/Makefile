CFLAGS = -Wall -Wextra -g
CPPFLAGS = -I.
LDFLAGS =

all: stack_tests

stack_tests: stack_tests.o stack.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

stack_tests.o: stack_tests.c stack.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $<

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $<

clean:
	rm -f stack_tests *.o

.PHONY: all clean
