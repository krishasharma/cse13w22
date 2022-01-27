CC = clang

CFLAGS = -Wall -Wextra -Werror -Wpedantic

ARES = sorting.o insert.o batcher.o heap.o quick.o stats.o

ATHENA = --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose

.PHONY: all clean scan-build valgrind

all: sorting 

sorting: $(ARES)
	$(CC) -o sorting $(ARES) 

sorting.o: sorting.c 
	$(CC) $(CFLAGS) -c sorting.c

insert.o: insert.c
	$(CC) $(CFLAGS) -c insert.c  

heap.o: heap.c 
	$(CC) $(CFLAGS) -c heap.c

batcher.o: batcher.c 
	$(CC) $(CFLAGS) -c batcher.c  

quick.o: quick.c 
	$(CC) $(CFLAGS) -c quick.c 

stats.o: stats.c 
	$(CC) $(CFLAGS) -c stats.c  

clean:
	rm -f stats quick batcher heap insert sorting stats.o quick.o batcher.o heap.o insert.o sorting.o 

scan-build: clean
	scan-build --use-cc=$(CC) make

valgrind: sorting 
	valgrind $(ATHENA) ./sorting -a -n 100 -p 0 

format:
	clang-format -i style=file *.[ch]
