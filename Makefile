CC=gcc
# -ansi -pedantic -Wconversion
CCWARN=-Wall -Wextra -Werror
CFLAGS=-O3 $(CCWARN) -g3

.PHONY: all
all: display roads

.PHONY: test
test: all
	# ./simple-terrain | display
	./display

.PHONY: testroads
testroads: all
	./roads | display

simple-terrain: simple-terrain.c
	$(CC) $< -o $@

display: display.o roam.o square.o
	$(CC) -lGLEW -lSDL -lGLU $^ -o $@

roads: roads.o
	$(CC) -lm $^ -o $@

# Create objects from C source code
%.o: %.c Makefile
	$(CC) -c $< $(CFLAGS) -o $@
