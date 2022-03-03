# Assignment 6: Huffman Coding

## Short Description: 
	The first task for this assignment is to implement a Huffman encoder. This encoder will read in an input file, find the Huffman encoding of its contents, and use the encoding to compress the file. The encoder program, named encode, must support any combination of the command-line options specified in the assignment 6 PDF. 
	The second task for this assignment is to implement a Huffman decoder. This decoder will read in a compressed input file and decompress it, expanding it back to its original, uncompressed size. Your decoder program, named decode, must support any combination of the command-line options specified in the assignment 6 PDF.
	
## Build 
        To build the program manually, type "clang -Wall -Wextra -Werror -Wpedantic -o <filename> <filename>.c" on the command line.
        Alternatively, type "make" on the command line, using the Makefile provided.

## Running
        To run the encoder program on the command line follow this structure for what to type: ./encode -i <infile> -o <outfile>
	To run the decoder program on the command line follow this structure for what to type: ./decode -i <infile> -o <outfile>
        To get the usage statements and synopsis type "./ -h" on the command line.

## Errors 
	The current version of my code is incomplete and encode and decode do not work as intended.

# Error Handling
	As the current version of my code is incomplete, running ./encode or ./decode will not give the desired output.
	Please refrence -h for the usage statements should an unknown error show up. 

## Cleaning 
        To clean manually, type "rm -f <filename> <filename>.o" on the command line
	Alternatively type "make clean" on the command line, using Makefile provided
 
~                     
