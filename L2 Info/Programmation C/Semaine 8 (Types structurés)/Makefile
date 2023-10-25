CFLAGS=-Wall -g -std=c99
all : student

student.o : student.c

student  : student.o all.o
	$(CC) $^ -o $@

clean:
	rm -f student student.o

.PHONY: all student