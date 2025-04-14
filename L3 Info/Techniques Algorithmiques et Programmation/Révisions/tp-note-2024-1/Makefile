CC = gcc
CFLAGS = -O3 -Wall -g -Wno-unused-function -Wno-deprecated-declarations -Wno-uninitialized -Wno-unused-result
LDLIBS = -lm

ifeq ($(shell uname -s), Darwin)
   LDLIBS += -framework OpenGL -framework GLUT
   CPPFLAGS += -I/opt/homebrew/include
else
   LDLIBS += -lglut -lGLU -lGL
   # parfois -lglut n'est pas nécessaire et peut-être supprimé
endif

LDLIBS += $(shell sdl2-config --libs)
LDFLAGS += $(shell sdl2-config --cflags)

main: htable.o main.o tools.o tp.o

.PHONY: clean
clean:
	rm -f *.o
	rm -f main
	rm -f tp
	rm -fr *.dSYM/
