CC = clang

CFLAGS = -Wall -Wextra -Werror -Wpedantic -g

MINOS = text.o parser.o bf.o bv.o speck.o ht.o pq.o node.o

MEDUSA = --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose

.PHONY: all scan-build valgrind

all: identify

test: $(MINOS) identify.o
	$(CC) -o identify $(MINOS) identify.o -lm

identify.o: identify.c
	$(CC) $(CFLAGS) -c identify.c 

clean:
	rm -f *.o node

scan-build: clean
	scan-build --use-cc=$(CC) make

valgrind: test
	valgrind $(MEDUSA) ./identify

format:
	clang-format -i -style=file *.[ch]
