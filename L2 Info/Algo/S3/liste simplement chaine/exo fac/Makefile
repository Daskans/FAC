CFLAGS = -Wall -Wextra -g -std=c99
LDLIBS = -lm

ALL: slist

slist: asde_slist.o tester_asde_slist.o asde_slist.h asde_slist_utilitary_functions.h
	$(CC) $^ $(LDLIBS) -o $@ 

asde_slist.o: asde_slist.c asde_slist.h asde_slist_utilitary_functions.h
	$(CC) $< -c 

tester_asde_slist.o: tester_asde_slist.c asde_slist.h asde_slist_utilitary_functions.h
	$(CC) $< -c 

clean:
	rm -f *.a *.o slist

.PHONY: ALL clean