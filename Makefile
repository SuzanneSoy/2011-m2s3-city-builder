CXX=g++
# -ansi -pedantic -Wconversion
CCWARN=-Wall -Wextra -Werror
# -flto (nécessite GCC 4.5) -m32 ou -m64
CFLAGS=-O0 -I. $(CCWARN)

OBJECTS = main.o view.o hash.o segment.o vertex.o triangle.o rules/chose.o rules/rectangleroutes.o rules/quad.o rules/quadroutes.o rules/route.o rules/carrefour.o rules/batiment.o
LIBS = -lm -lGL -lGLU -lSDL -lGLEW
EXECUTABLE = city

.PHONY: all
all: $(EXECUTABLE)
	./$(EXECUTABLE)

.PHONY: clean
clean:
	rm -f $(EXECUTABLE) all_includes.hh.d all_includes.hh.gch all.cpp

$(EXECUTABLE): $(OBJECTS:.o=.cpp) all_includes.hh.gch Makefile
	@:> all.cpp
	@$(foreach FILE,$(OBJECTS:.o=.cpp),echo '#include "'"$(FILE)"'"' >> all.cpp;)
	$(CXX) $(LIBS) $(CFLAGS) all.cpp -o $@
	@rm all.cpp

-include all_includes.hh.d
all_includes.hh.d:
all_includes.hh.gch: all_includes.hh Makefile
	$(CXX) $(CFLAGS) -MMD -MF all_includes.hh.d all_includes.hh -o all_includes.hh.gch
