CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

.PHONY: all clean 

all: integrate

integrate: integrate.o functions.o mathlib.o
	$(CC) -o integrate -lm integrate.o functions.o  mathlib.o 

functions.o: functions.c
	$(CC) $(CFLAGS) -c functions.c -o functions.o

mathlib.o: mathlib.c
	$(CC) $(CFLAGS) -c mathlib.c -o mathlib.o

integrate.o: integrate.c
	$(CC) $(CFLAGS) -c integrate.c 

clean:
	rm -f mathlib mathlib.o
