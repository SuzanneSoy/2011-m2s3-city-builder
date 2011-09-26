all: simple-terrain
	./simple-terrain | display

simple-terrain: simple-terrain.c
	gcc simple-terrain.c -o simple-terrain

display: display.c
	gcc -lGL -lSDL -lGLU display.c -o display
