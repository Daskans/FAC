# SDL2 Demo

This is a simple example that illustrates how to use SDL2 with a basic event
loop, transparent PNG textures, TTF fonts, ... It is designed to be compatible
with Android plaforms!

## Dependencies

```bash
apt install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev # for Linux Debian/Ubuntu
brew install sdl2 sdl2_image sdl2_ttf                     # for MacOS
```

## Compilation

With CMake:

```bash
mkdir build ; cd build ; cmake .. ; make VERBOSE=ON
```

Or without, if you prefer:

```bash
gcc -std=c99 -O3 -Wall -c -o main.o main.c
gcc -std=c99 -O3 -Wall -c -o demo.o demo.c
gcc -rdynamic -lm -lSDL2 -lSDL2_ttf -lSDL2_image demo.o main.o -o demo
```

## Run Demo

```bash
./demo
```

Move the bomb with keyboard arrows and move Mario with mouse. Press ESC to quit.
Enjoy this SDL2 sample!

## Model

An empty `model.c` is also available to easily start your own project!

```bash
gcc -std=c99 -O3 -Wall -c -o main.o main.c
gcc -std=c99 -O3 -Wall -c -o model.o model.c
gcc -rdynamic -lm -lSDL2 -lSDL2_ttf -lSDL2_image  model.o main.o -o model
```

---
<aurelien.esnard@u-bordeaux.fr>
