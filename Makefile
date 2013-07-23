CXX = g++
INCLUDE = -I/usr/include/qt4 \
          -I/usr/include/qt4/Qt \
          -I/usr/include/qt4/QtCore
#CXXFLAGS = -O3 -Wall -Wextra -g -std=c99 $(INCLUDE)
CXXFLAGS = -O0 -Wall -Wextra -g -std=c++11 $(INCLUDE) -DDEBUG
LN = $(CXX)
LIBS = -L/usr/lib/x86_64-linux-gnu/ -lm -lQtCore
LFLAGS = $(LIBS)

BINARY = quash

HEADERS = \
	complex.hpp \
	complexmatrix.hpp \
	complexvector.hpp \
	debug.hpp \
	real.hpp \

SOURCES = \
	complex.cpp \
	complexmatrix.cpp \
	complexvector.cpp \
	debug.cpp \
	main.cpp \
	real.cpp

all: dep $(BINARY)

$(BINARY): $(SOURCES) Makefile
	$(CXX) -o $(BINARY) $(SOURCES) $(CXXFLAGS) $(LFLAGS)
	@echo ""

dep: $(SOURCES)
	$(CXX) $(CXXFLAGS) -MM $^ > .depend

-include .depend

.PHONY: clean
clean:
	-rm -f $(BINARY) *.o *.h.gch

