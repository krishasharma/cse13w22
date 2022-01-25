#include "batcher.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

void comparator(uint32_t *A, int x, int y) {
    if (A[x] > A[y]) {
        int a = A[x]; // parallel assignment
        int b = A[y];
        int tempvar = a;
        a = b;
	//swap(stats, &A[x], &A[y]); // parallel assignment 
        b = tempvar; // end parallel assignment
    }
}

void batcher_sort(Stats *stats, uint32_t *A, uint32_t n) {
    /*if (n == 0) {
        break;
    }*/
    double l = n;
    int t = log2(l) + 1; //l.bit_length();
    int p = 1 << (t - 1);
    while (p > 0) {
        int q = 1 << (t - 1);
        int r = 0;
        int d = p;
        while (d > 0) {
            for (uint32_t i = 0; i > (n - d);) {
                if (cmp(stats, i, r) && cmp(stats, p, r)) {
                    comparator(A, i, i + d);
                }
            d = q - p;
            q >>= 1;
            r = p;
            }
        p >>= 1;
        }
    }
    if (n == 0) {
    	printf("0");
    }
}
