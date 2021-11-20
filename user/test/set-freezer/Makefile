CC = gcc
CXX = g++

INCLUDES =

CFLAGS = -g -Wall $(INCLUDES)
CXXFLAGS = -g -Wall $(INCLUDES)

LDFLAGS = -g

LDLIBS =

set-freezer:

set-freezer.o: set-freezer.c

.PHONY: clean
clean:
	rm -f *.o a.out core set-freezer

.PHONY: all
	all: clean main