CXX = g++
INCLUDE = \
	-I../../common \
	-I../../libquash \
	-I/usr/include/qt4 \
	-I/usr/include/qt4/Qt \
	-I/usr/include/qt4/QtCore
#CXXFLAGS = -O3 -Wall -Wextra -g -std=c99 $(INCLUDE)
CXXFLAGS = -O0 -Wall -Wextra -g -std=c++11 $(INCLUDE) -DDEBUG
LD = $(CXX)
ANY_LIBS = -L/usr/lib/x86_64-linux-gnu/ -lm -lQtCore -L../../libquash/
STATIC_LIBS = -lquash
LIBS =  -Wl,-Bstatic $(STATIC_LIBS) -Wl,-Bdynamic $(ANY_LIBS)
LFLAGS = $(LIBS)

BINARY = double-slit

SOURCES = main.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: dep $(BINARY)

$(BINARY): $(SOURCES) ../../libquash/libquash.a ../../libquash/libquash.so
	$(CXX) -o $(BINARY) $(SOURCES) $(CXXFLAGS) $(LFLAGS)

../../libquash/libquash.a:
	cd ../../libquash && make libquash.a

../../libquash/libquash.so:
	cd ../../libquash && make libquash.so

.PHONY: dep
dep: $(SOURCES)
	$(CXX) $(CXXFLAGS) -MM $^ > .depend

-include .depend

.PHONY: clean
clean:
	-rm -f $(BINARY) $(OBJECTS) *.h.gch .depend

