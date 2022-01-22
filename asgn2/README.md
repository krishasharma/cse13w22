# Assignment 2: Numerical Integration (README.md)

## Short Description: 
        This assignment has the two goals. The first is to implement our own small library of math functions, sin(x), cos(x), exponent, square root, and log(x). We are not allowed to use the <math.h> library to help with the first task. The second part of this assignment is to write a dedicated program, called integrate, that links with my implemented math library and computes numerical integrations of various functions using the composite Simpson’s ⅓ rule.

## Build 
        To build manually, type "clang -Wall -Wextra -Werror -Wpedantic -o integrate integrate.c" on the command line. 
	Alternatively, type "make" on the command line, using the Makefile provided.

## Running 
        To run the program on the command line follow this structure for what to type on the command line, "./integrate -<function> -p <low> -q <high> -n <partitions>". The low, high, and partitions must be numbers. 
	To get the usage statements and synopsis type "./integrate -H" on the command line. 

## Cleaning 
	make clean 
~                          
