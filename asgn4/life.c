#include <stdlib.h>
#include <stdio.h>
#include "universe.h"
#include <unistd.h>
#include <inttypes.h>
#include <stdbool.h>

int main() {
    uint32_t rows = 5;
    uint32_t cols = 10;
    bool toroidal = false;
    //uint32_t x = 3;
    //uint32_t y = 3;
    Universe *u = uv_create(rows, cols, toroidal);
    printf("rows : 5\n");
    printf("columns : 10\n");
    printf("cell 3,3 is alive\n");
    for (uint32_t i = 0; i < uv_cols(u); i++) {
        for(uint32_t j = 0; j < uv_rows(u); j++) {
            /*if (x == i) && (y == j) {
	        printf("o ");
	    }else {
	        printf(". ");
	    }*/ 
            printf("[%d, %d] ", i, j);
        }
        printf("\n");
    }
}
