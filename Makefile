CXX=g++
# -ansi -pedantic -Wconversion
CCWARN=-Wall -Wextra -Werror
CFLAGS=-O3 $(CCWARN) -g3

.PHONY: all
all: rules

.PHONY: clean
clean:
	rm rules *.o .*.d

rules: rules.o hash.o
	$(CXX) -lm $^ -o $@

-include .*.d

%.o: %.cpp Makefile
	$(CXX) -MMD -MF .$(@:.o=.d) -c $< $(CFLAGS) -o $@
