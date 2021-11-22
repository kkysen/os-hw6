CC = gcc

INCLUDES =

CFLAGS = -std=c11 -g -Wall -Werror -Wextra $(INCLUDES)

LDFLAGS = -g

LDLIBS =

set-freezer: set-freezer.o

set-freezer.o: set-freezer.c

.PHONY: clean
clean:
	rm -f *.o a.out core* set-freezer

.PHONY: all
all: clean main
