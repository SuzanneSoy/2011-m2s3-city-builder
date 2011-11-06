CXX=g++
# -ansi -pedantic -Wconversion
CCWARN=-Wall -Wextra -Werror
CFLAGS=-O3 $(CCWARN) -g3

OBJECTS = main.o hash.o segment.o vertex.o io.o rules/rectangleroutes.o rules/route.o rules/carrefour.o
EXECUTABLE = city

.PHONY: test
test: all
	./$(EXECUTABLE)

.PHONY: all
all: $(EXECUTABLE)

.PHONY: clean
clean:
	rm -f $(EXECUTABLE) $(OBJECTS) $(OBJECTS:.o=.d)

city: $(OBJECTS)
	$(CXX) -lm $^ -o $@

-include $(OBJECTS:.o=.d)

%.o: %.cpp Makefile
	$(CXX) -MMD -MF $(@:.o=.d) -c $< $(CFLAGS) -o $@
