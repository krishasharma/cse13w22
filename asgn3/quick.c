#include "quick.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// this code is based off of pusedocode provided by Professor Long 
// the pusedocode was given in the assignment PDF and the discord
// please note that I have high psuedo code collaboration with my sister Twisha Sharma (tvsharma) 

uint32_t partition(Stats *stats, uint32_t *A, uint32_t low, uint32_t high) {
    uint32_t i = low - 1;
    for (uint32_t j = low; j < high; j += 1) { 
    if (cmp(stats, A[j - 1], A[high - 1]) == -1) {
            i += 1;
	    swap(stats, &A[i - 1], &A[j - 1]);
        }
	//swap(stats, &A[i], &A[high - 1]);
    }
    swap(stats, &A[i], &A[high - 1]);
    return i + 1;
}

void quick_sorter(Stats *stats, uint32_t *A, uint32_t low, uint32_t high) {
    if (low < high) {
        uint32_t p = partition(stats, A, low, high);
        quick_sorter(stats, A, low, p - 1);
        quick_sorter(stats, A, p + 1, high);
    }
}

void quick_sort(Stats *stats, uint32_t *A, uint32_t n) {
    quick_sorter(stats, A, 1, n);
}
