CC=gcc
# -ansi -pedantic -Wconversion
CCWARN=-Wall -Wextra -Werror
CFLAGS=-O3 $(CCWARN) -g3

.PHONY: all
all: display roads rules

.PHONY: test
test: display
	./display

.PHONY: test
test-simple-terrain: simple-terrain
	./simple-terrain | display

.PHONY: testroads
testroads: roads
	./roads | display

.PHONY: clean
clean:
	rm simple-terrain display roads rules *.o

simple-terrain: simple-terrain.c
	$(CC) $< -o $@

display: display.o roam.o square.o hash.o
	$(CC) -lGLEW -lSDL -lGLU $^ -o $@

roads: roads.o
	$(CC) -lm $^ -o $@

rules: rules.o hash.o
	$(CC) -lm $^ -o $@

-include .*.d

%.o: %.c Makefile
	$(CC) -MMD -MF .$(@:.o=.d) -c $< $(CFLAGS) -o $@
