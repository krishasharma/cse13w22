CC = clang

CFLAGS = -Wall -Wextra -Werror -Wpedantic -g

HERA = huffman.o io.o stack.o code.o pq.o node.o

HERMES = --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose

.PHONY: all scan-build valgrind

all: encode decode

encode: $(HERA) encode.o
	$(CC) -o encode $(HERA) encode.o

encode.o: encode.c
	$(CC) $(CFLAGS) -c encode.c

decode: $(HERA) decode.o
	$(CC) -o decode $(HERA) decode.o

decode.o: decode.c
	$(CC) $(CFLAGS) -v decode.c

clean:
	rm -f *.o encode decode huffman io stack code pq node

scan-build: clean
	scan-build --use-cc=$(CC) make

valgrind: test
	valgrind $(HERMES) ./encode

format:
	clang-format -i -style=file *.[ch]
