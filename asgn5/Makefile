CC = clang

CFLAGS = -Wall -Wextra -Werror -Wpedantic -g $(shell pkg-config --cflags gmp)

HERA =  randstate.o numtheory.o rsa.o

HERMES = --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose

LFLAGS = $(shell pkg-config --libs gmp)

.PHONY: all scan-build valgrind format 

all: keygen encrypt decrypt 

keygen: $(HERA) keygen.o 
	$(CC) -o keygen $(HERA) keygen.o $(LFLAGS)

keygen.o: keygen.c
	$(CC) $(CFLAGS) -c keygen.c

encrypt: $(HERA) encrypt.o
	$(CC) -o encrypt $(HERA) encrypt.o $(LFLAGS)

encrypt.o: encrypt.c
	$(CC) $(CFLAGS) -c encrypt.c

decrypt: $(HERA) decrypt.o
	$(CC) -o decrypt $(HERA) decrypt.o $(LFLAGS)

decrypt.o: decrypt.c
	$(CC) $(CFLAGS) -c decrypt.c

clean:
	rm -f *.o keygen
	rm -f *.o encrypt	
	rm -f *.o decrypt

scan-build: clean
	scan-build --use-cc=$(CC) make 

valgrind: keygen
	valgrind $(HERMES) ./keygen

format:
	clang-format -i -style-file *.[ch]

