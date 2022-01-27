#include "batcher.h"
#include "heap.h"
#include "set.h"
#include "insert.h"
#include "quick.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h> 
#include <stdbool.h>

void bye(uint32_t *A, uint32_t size, uint32_t seed){
    srandom(seed);
    uint32_t z = 0;
    for (z = 0; z < size; z++) {
        A[z] = random() & 0x3FFFFFFF;
    }
    return;
}

int main(int argc, char **argv) { // use getopt() loop to parse arguments
    Stats statistics = {0, 0};
    Set setsort = empty_set(); // makes an empty set, returns a set of 64 bit
    int opt = 0;
    uint32_t seed = 13371453;
    uint32_t size = 100;
    uint32_t elements = 100; 
    while ((opt = getopt(argc, argv, "ahbiqr:n:p:H")) != -1) {
        switch (opt) {
	// -a employs all sorting algorithims 
        case 'a': 
            setsort = insert_set(1, setsort);
	    setsort = insert_set(2, setsort);
	    setsort = insert_set(3, setsort);
	    setsort = insert_set(4, setsort);
            break;
	// enables heap sort 
        case 'h': 
	    setsort = insert_set(1, setsort);
	    break;
	// enables batcher sort 
	case 'b':
	    setsort = insert_set(2, setsort);
	    break;
	// enables insertion sort 
	case 'i': 
	    setsort = insert_set(3, setsort);
	    break;
	// enables quicksort
	case 'q': 
	    setsort = insert_set(4, setsort);
	    break;
	case 'r': // seed: set the random seed to seed. the defualt seed should be 13371453.
	    seed = strtod(optarg, NULL);
	    break;
	case 'n': // size: set the array size to size. The defualt size should be 100.
	    size = strtod(optarg, NULL);
	    elements = size;
	    break;
	// elements: print out elements number of elements from the array. The default is 100
	case 'p':
	    elements = strtod(optarg, NULL);
	    break;
	// prints out the program usage. 
	case 'H':
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
    
    uint32_t *A = (uint32_t *)malloc(size * sizeof(uint32_t));

    if (member_set(1, setsort) == true) { 
        // heap sort -h
	bye(A, size, seed);
	heap_sort(&statistics, A, size);
	printf("Heap Sort, %d elements, %lu moves, %lu comparasion\n", size, statistics.moves, statistics.compares);
        uint32_t i = 0;
        while(i < elements) {
            printf("%13" PRIu32, A[i]);
            i += 1;
            if (i % 5 == 0) {
                printf("\n");
                }
        }
	printf("\n");
        reset(&statistics); // reset the array or re initialize the array at zero  
    }

    if (member_set(2, setsort) == true) {
        // batchers sort -b 
	bye(A, size, seed);
	batcher_sort(&statistics, A, size);
	printf("Batchers Sort, %d elements, %lu moves, %lu comparasion\n", size, statistics.moves, statistics.compares);
	uint32_t i = 0;
        while(i < elements) {
            printf("%13" PRIu32, A[i]);
            i += 1;
            if (i % 5 == 0) {
                printf("\n");
                }
        }
	printf("\n");
        reset(&statistics); // reset the array or re initialize the array at zero 
    }

    if (member_set(3, setsort) == true) {
        // insertion sort -i
	bye(A, size, seed); 
	insertion_sort(&statistics, A, size);
	printf("Insertion Sort, %d elements, %lu moves, %lu comparasion\n", size, statistics.moves, statistics.compares);
	uint32_t i = 0;
        while(i < elements) {
            printf("%13" PRIu32, A[i]);
            i += 1;
            if (i % 5 == 0) {
                printf("\n");
                }
        }
        printf("\n");
        reset(&statistics); // reset the array or re initialize the array at zero 
    }

    if (member_set(4, setsort) == true) {
    	// quick sort -q
	bye(A, size, seed);
	quick_sort(&statistics, A, size);
	printf("Quick Sort, %d elements, %lu moves, %lu comparasion\n", size, statistics.moves, statistics.compares);
        uint32_t i = 0;
        while(i < elements) {
            printf("%13" PRIu32, A[i]);
            i += 1;
            if (i % 5 == 0) {
                printf("\n");
                }
        }
        printf("\n");
        reset(&statistics); // reset the array or re initialize the array at zero 
    }

    free(A);
    return 0;

}
