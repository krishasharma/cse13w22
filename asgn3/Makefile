CC = clang

CFLAGS = -Wall -Wextra -Werror -Wpedantic

.PHONY: all clean

all: sorting 

sorting: insert.o heap.o batcher.o quick.o stats.o 
	$$(CC) -o sorting -lm sorting.o insert.o heap.o batcher.o quick.o stats.o 

insert.o: insert.c
	$(CC) $(CFLAGS) -c insert.c -o insert.o 

heap.o: heap.c 
	$(CC) $(CFLAGS) -c heap.c -o heap.o 

batcher.o: batcher.c 
	$(CC) $(CFLAGS) -c batcher.c -o batcher.o 

quick.o: quick.c 
	$(CC) $(CFLAGS) -c qick.c -o quick.o 

stats.o: stats.c 
	$(CC) $(CFLAGS) -c stats.c -o stats.o 

clean:
	rm -f stats quick batcher heap insert sorting stats.o quick.o batcher.o heap.o insert.o sorting.o 

format:
	clang-format -i style=file *.[ch]
