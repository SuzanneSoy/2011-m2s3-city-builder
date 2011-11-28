CXX=g++
# -ansi -pedantic -Wconversion
CCWARN=-Wall -Wextra -Werror
# -flto (nécessite GCC 4.5) -m32 ou -m64
CFLAGS=-O3 -g3 -I. $(CCWARN)

OBJECTS = main.o hash.o segment.o vertex.o triangle.o gputriangles.o rules/chose.o rules/rectangleroutes.o rules/route.o rules/carrefour.o rules/batiment.o
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
