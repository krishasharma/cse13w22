CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

.PHONY: all

all: mathlib

testFile: testFile.o mathlib.o
        $(CC) -o testFile testFile.o mathlib.o

mathlib: mathlib.o
        $(CC) -o mathlib mathlib.o

mathlib.o: mathlib.c
        $(CC) $(CFLAGS) -c mathlib.c -o mathlib.o

testFile.o: testFile.c
        $(CC) $(CFLAGS) -c testFile.c

clean:
	rm -f mathlib mathlib.o 
~
