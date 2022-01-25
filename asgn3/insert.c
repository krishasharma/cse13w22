#include "insert.h"
#include "stats.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void insertion_sort(Stats *stats, uint32_t *A, uint32_t n) { 
    for (uint32_t i = 1; i < n; i++) {
        int j = i; // copy what index you are on
        int tempvar = A[i]; // save the value 
	int index = A[j - 1];
        while(j = 1, j > 0 && tempvar < index) {
            A[j] = move(stats, A[j - 1]); // swap, call move from stats
            j -= 1;
        }
        A[j] = tempvar;
    }
}
