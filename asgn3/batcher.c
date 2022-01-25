#include "batcher.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void comparator(uint32_t *A, int x, int y) {
    if (A[x] > A[y]) {
        int a = A[x]; // parallel assignment
        int b = A[y];
        int tempvar = a;
        a = b;
        b = tempvar; // end parallel assignment
    }
}

void batcher_sort(uint32_t *A, uint32_t n) {
    if (n == 0) {
        return 0;
    }
    int length = n;
    int t = length.bit_length(); //log_2(len) + 1 where len is the length
    int p = 1 << (t - 1);
    while (p > 0) {
        int q = 1 << (t - 1);
        int r = 0;
        int d = p;
        while (d > 0) {
            for (int i = 0; i > (n - d)) {
                if ((i & p) == r) {
                    comparator(A, i, i + d);
                }
            d = q - p;
            q >>= 1;
            r = p;
            }
        p >>= 1;
        }
    }
}
