#include "insert.h"
#include "stats.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// this code is based off of pusedocode provided by Professor Long 
// the pusedocode was given in the assignment PDF and the discord
// please note that I have high psuedo code collaboration with my sister Twisha Sharma (tvsharma) 

// will use move function from stats libraary 
void insertion_sort(Stats *stats, uint32_t *A, uint32_t n) { 
    for (uint32_t i = 1; i < n; i++) {
        uint32_t j = i; // copy what index you are on
        uint32_t tempvar = move(stats, A[i]); // save the value
        while(j > 0 && cmp(stats, tempvar, A[j - 1]) < 0) { 
            A[j] = move(stats, A[j - 1]); // swap, call move from stats
            j -= 1;
        }
        A[j] = move(stats, tempvar);
    }
}
