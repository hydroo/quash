AR = ar
CXX = g++-4.8
INCLUDE = \
	-I../common \
	-I/usr/include/qt5 \
	-I/usr/include/qt5/Qt \
	-I/usr/include/qt5/QtCore
#CXXFLAGS = -O3 -Wall -Wextra -g -std=c99 $(INCLUDE)
CXXFLAGS = -O0 -Wall -Wextra -g -std=c++11 -fPIC $(INCLUDE) -DDEBUG
LD = $(CXX)
LIBS = -L/usr/lib/x86_64-linux-gnu/ -lm -lQt5Core
LFLAGS = $(LIBS)

SHARED_LIBRARY = libquash.so
STATIC_LIBRARY = libquash.a

HEADERS = \
	../common/debug.hpp \
	../common/misc.hpp \
	complex.hpp \
	complexmatrix.hpp \
	complexvector.hpp \
	real.hpp \
	state.hpp

SOURCES = \
	../common/debug.cpp \
	../common/misc.cpp \
	complex.cpp \
	complexmatrix.cpp \
	complexvector.cpp \
	real.cpp \
	state.cpp

OBJECTS = $(SOURCES:.cpp=.o)

all: dep $(STATIC_LIBRARY) $(SHARED_LIBRARY)

$(STATIC_LIBRARY): $(OBJECTS)
	$(AR) rcs $(STATIC_LIBRARY) $(OBJECTS)
	@echo ""

$(SHARED_LIBRARY): $(OBJECTS)
	$(LD) -shared -o $(SHARED_LIBRARY) $(OBJECTS)
	@echo ""

%.o: %.cpp
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c $< -o $@

.PHONY: dep
dep: $(SOURCES)
	$(CXX) $(CXXFLAGS) -MM $^ > .depend

-include .depend

.PHONY: clean
clean:
	-rm -f $(SHARED_LIBRARY) $(STATIC_LIBRARY) $(OBJECTS) *.h.gch .depend

