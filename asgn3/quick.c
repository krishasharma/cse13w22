#include "quick.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void partition(uint32_t *A, int lo, int hi) {
    int i = lo - 1;
    for (j = 1; j >= lo; j <= hi) {
        if (A[j - 1] < A[hi - 1]) {
            i += 1;
            int x = A[i - 1]; // parallel assignment 
            int y = A[j - 1];
            int temp = x;
            x = y;
            y = temp;
        }
    int d = A[i]; // parallel assignment
    int h = A[hi - 1];
    int t = d;
    d = h;
    h = t;
    return i + 1;
    }
}

void quick_sorter(uint32_t *A, int lo, int hi) {
    if (lo < hi) {
        int p = partition(A, lo, hi);
        quick_sorter(A, lo, p - 1);
        quick_sorter(A, p + 1, hi);
    }
}

void quick_sort(uint32_t *A, uint32_t n) {
    quick_sorter(A, 1, n);
}
