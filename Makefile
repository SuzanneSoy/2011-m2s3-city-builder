CC=gcc
# -ansi -pedantic -Wconversion
CCWARN=-Wall -Wextra -Werror
CFLAGS=-O3 $(CCWARN)

.PHONY: all
all: simple-terrain display roam

.PHONY: test
test: all
	./simple-terrain | display
	./display
	./roam

simple-terrain: simple-terrain.c Makefile
	$(CC) $< -o $@

display: display.c Makefile
	$(CC) -lGL -lSDL $< $(CFLAGS) -o $@

roam: roam.c Makefile
	$(CC) $< $(CFLAGS) -o $@

# Create objects from C source code
%.o: %.c
	$(CC) -c $< $(CFLAGS) -o $@
