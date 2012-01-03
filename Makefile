CXX=g++
# -ansi -pedantic -Wconversion
CCWARN=-Wall -Wextra -Werror
# TODO : -O3 -m32 ou -m64
# -g -rdynamic uniquement pour le debug.
CFLAGS=-O0 -I. $(CCWARN) -g -rdynamic

SOURCES = $(shell echo *.cpp geometry/*.cpp rules/*.cpp rules/*/*.cpp)
HEADERS = $(shell echo *.hh  geometry/*.hh  rules/*.hh  rules/*/*.hh)
LIBS = -lm -lGL -lGLU -lSDL -lGLEW
EXECUTABLE = city

.PHONY: all
all: $(EXECUTABLE)
	./$(EXECUTABLE)

.PHONY: clean
clean:
	rm -f $(EXECUTABLE) all_includes.hh.gch all.cpp

$(EXECUTABLE): $(SOURCES) all_includes.hh.gch Makefile
	@echo "#ifndef _ALL_CPP_"> all.cpp
	@echo "#define _ALL_CPP_">> all.cpp
	@$(foreach FILE,$(SOURCES),echo '#include "'"$(FILE)"'"' >> all.cpp;)
	@echo "#endif">> all.cpp
	$(CXX) $(LIBS) $(CFLAGS) all.cpp -o $@
	@rm all.cpp

all_includes.hh.gch: $(HEADERS) Makefile
	$(CXX) $(CFLAGS) all_includes.hh -o all_includes.hh.gch
