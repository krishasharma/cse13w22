#include "universe.h"
#include <stdlib.h>
#include <stdio.h>

struct Universe {
    uint32_t rows;
    uint32_t cols;
    bool **grid; // 2D array
    bool torodial; 
}; // how a non-typedef struct is made

Universe *uv_create(uint32_t rows, uint32_t cols, bool toroidal) {
    Universe *u = (Universe *) calloc(toroidal, sizeof(Universe)); // gives me a pointer to allocate a  memory big enough to contain Universe
    bool **grid = (bool **) calloc(rows, sizeof(bool *)); // **grid was previosuly **matrix 
    for(uint32_t r = 0; r < rows; r += 1) {
        grid[r] = (bool *) calloc(cols, sizeof(bool)); // allocates a column of pointers to rows then allocate the actual rows 
    }
    u->rows = rows;
    u->cols = cols;
    /*if (u != NULL) { 
        u->rows = rows;
        u->cols = cols;
        //u->grid[r][c] = (bool **) calloc(grid ,sizeof(bool)); // allocates the memory of the grid to the size of the Universe      
    }
    if (!u->grid) {
        free(u);
        bv = NULL;
    }*/
    return u;
}

void uv_delete(Universe *u) { // destructor function
    if(!u -> grid) {
        free(u);
	u = NULL;
    }
}

uint32_t uv_rows(Universe *u) { // returns the number of rows in the Universe 
    return u->rows;
}

uint32_t uv_cols(Universe *u) { // returns the number of columns in the Universe
    return u->cols;
}

void uv_live_cell(Universe *u, uint32_t r, uint32_t c) { // marks cell at row r and column c as live 
    if (r > 0 && r < uv_rows(u)) {
	if (c > 0 && c < uv_cols(u)) {
	    u->grid[r][c] = true;
	}
    }
}

void uv_dead_cell(Universe *u, uint32_t r, uint32_t c) { // marks cell at row r and column c as dead 
    if (r > 0 && r < uv_rows(u)) {
        if (c > 0 && c < uv_cols(u)) {
	    u->grid[r][c] = false;
	}
    }
}

bool uv_get_cell(Universe  *u, uint32_t r, uint32_t c) { // returns the value of cell at row r and column c 
    return 0;
}

bool uv_populate(Universe *u, FILE *infile) { // populates the Universe with row-column pairs read in from infile
    /*fscanf(row) // pusedocode for uv_populate
    fscanf(col)
    while (fscan(infile, %, <some var>) != end of file){
        fscanf(&in_row)
        fscanf(&in_col)
    }
    if (not in grid){
        return false
    }
    set live cell
    return true*/ 
    return 0;
}
