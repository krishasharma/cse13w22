#include "batcher.h"
#include "heap.h"
#include "insert.h"
#include "quick.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h> 

int main(int argc, char **argv) { // use getopt() loop to parse arguments
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
	// seed: set the random seed to see. the defualt seed should be 13371453
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
	    break;
        default:
            fprintf(stderr, "error\n");
            return 1;
        }
    }

    if (i_a) {
       printf("%13" PRIu32, );
    }


}
