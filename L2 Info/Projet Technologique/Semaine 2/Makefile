CC = gcc
AR = ar
CFLAGS = -Wall -std=c99
LDFLAGS = -L.
LDLIBS = -lgame
ALL: game_text libgame.a

game_text: game_text.o libgame.a
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

game_text.o: game_text.c libgame.a game.h game_aux.h

clean:
	rm -f *.o game_text

.PHONY: ALL clean

