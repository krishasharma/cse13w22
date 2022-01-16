CC = clang 
CFLAGS = -Wall -Wextra -Werror -Wpedantic 

.PHONY: all 

all: testfile 

testfile: testfile.o 
	$(CC) -o testfile testfile.o 

testfile.o: testfile.c 
	$(CC) $(CFLAGS) -c testfile.c -o testfile.o 

clean: 
	rm -f testfile testfile.o 
