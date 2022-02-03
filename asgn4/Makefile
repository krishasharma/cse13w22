CC = clang 

CFLAGS = -Wall -Werror -Wextra -Wpedantic -g `pkg-config --cflags ncurses`

LFLAGS = $(shell pkg-config --libs ncurses)

.PHONY: all clean format scan-build valgrind

CERBERUS = life.o universe.o  

CIRCE = --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose

all: life

life: $(CERBERUS)
	$(CC) -o life $(CERBERUS) -lncurses

universe.o: universe.c
	$(CC) $(CFLAGS) -c universe.c

life.o: life.c
	$(CC) $(CFLAGS) -c life.c

clean: 
	rm -f universe life universe.o life.o 

scan-build: clean
	scan-build --use-cc=$(CC) make

valgrind: life
	valgrind $(CIRCE) ./life

format: 
	clang-format -i style=file *.[ch]
