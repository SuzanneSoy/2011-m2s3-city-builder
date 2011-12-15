CXX=g++
# -ansi -pedantic -Wconversion
CCWARN=-Wall -Wextra -Werror
# -flto (nécessite GCC 4.5) -m32 ou -m64
CFLAGS=-O0 -I. $(CCWARN)

SOURCES = $(shell echo *.cpp rules/*.cpp rules/*/*.cpp)
LIBS = -lm -lGL -lGLU -lSDL -lGLEW
EXECUTABLE = city

.PHONY: all
all: $(EXECUTABLE)
	./$(EXECUTABLE)

.PHONY: clean
clean:
	rm -f $(EXECUTABLE) all_includes.hh.d all_includes.hh.gch all.cpp

$(EXECUTABLE): $(SOURCES) all_includes.hh.gch Makefile
	@echo "#ifndef _ALL_CPP_"> all.cpp
	@echo "#define _ALL_CPP_">> all.cpp
	@$(foreach FILE,$(SOURCES),echo '#include "'"$(FILE)"'"' >> all.cpp;)
	@echo "#endif">> all.cpp
	$(CXX) $(LIBS) $(CFLAGS) all.cpp -o $@
	@rm all.cpp

-include all_includes.hh.d
all_includes.hh.d:
all_includes.hh.gch: all_includes.hh Makefile
	$(CXX) $(CFLAGS) -MMD -MF all_includes.hh.d all_includes.hh -o all_includes.hh.gch
