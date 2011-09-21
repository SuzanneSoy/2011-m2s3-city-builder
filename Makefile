all: simple-terrain
	./simple-terrain | display

simple-terrain: simple-terrain.c
	gcc simple-terrain.c -o simple-terrain
