#include "insert.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void insertion_sort(uint32_t *A, uint32_t n) {
    for (int i = 1; i < n; i++) {
        int j = i;
        tempvar = A[i];
        while(j = 1, j > 0 && tempvar < A[j - 1]) {
            int A[j] = A[j - 1];
            j -= 1;
        }
        A[j] = tempvar;
    }
}
