#include "batcher.h"
#include "heap.h"
#include "insert.h"
#include "quick.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h> 
#include <stdbool.h>

int main(int argc, char **argv) { // use getopt() loop to parse arguments
    Stats statistics = {0, 0}
    int opt = 0;
    bool i_a = false;
    bool i_h = false;
    bool i_b = false;
    bool i_i = false;
    bool i_q = false;
    bool i_r = false;
    bool i_n = false;
    bool i_p = false;
    bool i_H = false;
    while ((opt = getopt(argc, argv, "ahbiq:r:n:p:H")) != -1) {
        switch (opt) {
	// -a employs all sorting algorithims 
        case 'a':
            i_a = true;
            break;
	// enables heap sort 
        case 'h':
	    i_h = true;
	    break;
	// enables batcher sort 
	case 'b':
	    i_b = true;
	    break;
	// enables insertion sort
	case 'i':
	    i_i = true;
	    break;
	// enables quicksort
	case 'q':
	    i_q = true;
	    break;
	// seed: set the random seed to see. the defualt seed should be 13371453.
	case 'r':
	    i_r = true;
	    break;
	// size: set the array size to size. The defualt size should be 100.
	case 'n':
	    i_n = true;
	    break;
	// elements: print out elements number of elements from the array. The default is 100
	case 'p':
	    i_p = true;
	    break;
	// prints out the program usage. 
	case 'H':
	    i_H = true;
	    printf(" -a: employs all sorting algorithims\n");
	    printf(" -h: enables heap sort\n");
	    printf(" -b: enables batchers sort\n");
	    printf(" -i: enables insertion sort\n");
	    printf(" -q: enables quicksort\n");
	    printf(" -r: seed: set the random seed to see. the defualt seed should be 13371453\n");
	    printf(" -n: size: set the array size to size. The defualt size should be 100.\n");
	    printf(" -p: elements: print out elements number of elements from the array. The default is 100.\n");
	    printf(" -H: prints out the program usage.\n");
	    break;
        default:
            fprintf(stderr, "error\n");
            return 1;
        }
    }

    uint32_t A[size];
    srand(seed);
    int count;
    for (k = 0; count < size; count++) {
    	A[count] = rand();
    }

    if (i_a) {
        // this if statement will print out all the sorting algorithims  	
        printf("%13" PRIu32, statistics);
    }

    if (i_h) {
        // heap sort 
    }

    if (i_b) {
        // batchers sort 
    }

    if (i_i) {
        // insertion sort
	printf("yay"\n);
    	return stats;
	printf("Insertion Sort", elements, moves, compares);
    }

    if (i_q) {
    	// quick sort 
	printf("quick sort"\n);
    }

    if (i_n) {
        // set the array size to size
    }
}
