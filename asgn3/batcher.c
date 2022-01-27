#include "batcher.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

// this code is based off of pusedocode provided by Professor Long 
// the pusedocode was given in the assignment PDF and the discord 
// please note that I have high psuedo code collaboration with my sister Twisha Sharma (tvsharma)

void comparator(Stats *stats, uint32_t *A, uint32_t x, uint32_t y) {
    if (cmp(stats, A[x], A[y]) == 1) { // COMPARE cause A[x] > A[y] 
        swap(stats, &A[x], &A[y]);
    }
}

uint32_t bitlen(uint32_t value) { // bit length
    uint32_t counter = 0;
    while (value > 0) {
        counter += 1;
	value /= 2;
    }
    return counter;
}

void batcher_sort(Stats *stats, uint32_t *A, uint32_t n) {
    if (n == 0) {
        return;
    }
    uint32_t t = bitlen(n); // same as l.bit_length();
    uint32_t p = 1 << (t - 1);
    while (p > 0) {
        uint32_t q = 1 << (t - 1);
        uint32_t r = 0;
        uint32_t d = p;
        while (d > 0) {
            for (uint32_t i = 0; i < (n - d); i += 1 ) {
                if ((i & p) == r) {
                    comparator(stats, A, i, i + d);
                }
	    }
	    d = q - p;
            q >>= 1;
            r = move(stats, p); // MOVE cause r = p
        }
        p >>= 1;
    }
}
