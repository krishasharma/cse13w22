CC = clang

CFLAGS = -Wall -Wextra -Werror -Wpedantic -g $(shell pkg-config --cflags gmp)

HERA =  randstate.o test.o numtheory.o rsa.o

HERMES = --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose

LFLAGS = $(shell pkg-config --libs gmp)

.PHONY: all scan-build valgrind format 

all: test

test: $(HERA)
	$(CC) -o test $(HERA) $(LFLAGS)

test.o: test.c
	$(CC) $(CFLAGS) -c test.c

clean:
	rm -f *.o test

scan-build: clean
	scan-build --use-cc=$(CC) make

valgrind: test
	valgrind $(HERMES) ./test

format:
	clang-format -i -style-file *.[ch]

