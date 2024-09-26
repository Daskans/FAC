.PHONY: clean all

SOURCES	:= $(wildcard ../*.c)
PROGS	:= $(SOURCES:%.c=%)

#CC		:= gcc
CFLAGS	:= -O3 -Wall

all: $(PROGS)

clean:
	rm -f *.exe *.o *.bin ../*.exe ../*.o ../*.bin