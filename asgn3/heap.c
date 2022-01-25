#include "heap.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void max_child(uint32_t *A, int first, int last) {
    int left = 2 * first;
    int right = left + 1;
    if (right <= last, A[right - 1] > A[left - 1]) {
        return right;
    }
    else {
        return left;
    }
}

void fix_heap(uint32_t *A, int first, int last) {
    bool found = False;
    int mother = first;
    int great = max_child(A, mother, last);
    while (mother <= last / 2 && mother != found) {
        if ( A[mother -1] < A[great - 1]) {
            int x = A[mother - 1]; // Parallel assignment, swap the variables
            int y = A[great - 1];
            int tempvar = x;
            x = y;
            y = tempvar; // end parallel assignment
            mother = great;
            great = max_child(A, mother, last);
        }
        else {
            bool found = True;
        }
    }
}

void build_heap(uint32_t *A, int first, int last) {
    for (int father = last / 2; father < first - 1; father - 1) { // This loop might be wrong 
        fix_heap(A, father, last);
    }
}

void heap_sort(uint32_t *A, uint32_t n) {
    int first = 1;
    int last = n;
    build_heap(A, first, last);
    for (int leaf = 1; leaf < last; leaf -= 1) {
        int x = A[first - 1]; // parallel assignment 
        int y = A[leaf - 1];
        int tempvar = x;
        x = y;
        y = tempvar; // end parallel assignment
        fix_heap( A, first, leaf - 1);
    }
}
