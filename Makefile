CC=gcc
# -ansi -pedantic -Wconversion
CCWARN=-Wall -Wextra -Werror
CFLAGS=-O3 $(CCWARN) -g3

.PHONY: all
all: display

.PHONY: test
test: all
	# ./simple-terrain | display
	./display

simple-terrain: simple-terrain.c
	$(CC) $< -o $@

display: display.o roam.o square.o
	$(CC) -lGLEW -lSDL -lGLU $^ -o $@

# Create objects from C source code
%.o: %.c Makefile
	$(CC) -c $< $(CFLAGS) -o $@
