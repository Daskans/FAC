CFLAGS=-Wall -g -std=c99
VAR = [NOTE]BarCode

all : $(VAR)

$(VAR).o : $(VAR).c

$(VAR) : $(VAR).o all.o
	$(CC) $^ -o $@

clean:
	rm $(VAR) $(VAR).o

.PHONY: all $(VAR)