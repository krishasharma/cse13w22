#include "universe.h"
#include <stdlib.h>
#include <stdio.h>

struct Universe {
    uint32_t rows;
    uint32_t cols;
    bool **grid; // 2D array
    bool toroidal;
};

// function that creates the grid that the game is played on
Universe *uv_create(uint32_t rows, uint32_t cols, bool toroidal) {
    Universe *u = (Universe *) calloc(1, sizeof(Universe)); // one universe created,gives me a pointer to allocate a  memory big enough to contain Universe
    //u->grid = malloc(sizeof(Universe));
    bool **grid = (bool **) calloc(rows, sizeof(bool *)); // **grid was previosuly **matrix
    for (uint32_t r = 0; r < rows; r += 1) {
        grid[r] = (bool *) calloc(cols,sizeof(bool)); // allocates a column of pointers to rows then allocate the actual rows
    }
    u->rows = rows;
    u->cols = cols;
    u->toroidal = toroidal;
    u->grid = grid;
    return u;
}

// destructor function
void uv_delete(Universe *u) {
    for (uint32_t r = 0; r < uv_rows(u); r += 1) {
        free(u->grid[r]);
        u->grid[r] = NULL;
    }
    free(u->grid); // first free whats inside the universe
    u->grid = NULL;
    free(u); // then free the universe
    u = NULL;
}

// returns the number of rows in the Universe
uint32_t uv_rows(Universe *u) {
    return u->rows;
}

// returns the number of columns in the Universe
uint32_t uv_cols(Universe *u) {
    return u->cols;
}

// marks cell at row r and column c as live
void uv_live_cell(Universe *u, uint32_t r, uint32_t c) {
    u->grid[r][c] = true;
    /*if (r < uv_rows(u)) {
        if (c < uv_cols(u)) {
            u->grid[r][c] = true;
        }
    }*/
}

// marks cell at row r and column c as dead
void uv_dead_cell(Universe *u, uint32_t r, uint32_t c) {
    if (r > 0 && r < uv_rows(u)) {
        if (c > 0 && c < uv_cols(u)) {
            u->grid[r][c] = false;
        }
    }
}

// returns the value of cell at row r and column c
bool uv_get_cell(Universe *u, uint32_t r, uint32_t c) {
    if (r < 0 || c < 0 || r >= uv_rows(u) || c >= uv_cols(u)) {
        return false;
    }
    return u->grid[r][c];
}

// populates the Universe with row-column pairs read in from infile
bool uv_populate(Universe *u, FILE *infile) {
    // reads a pair of cooridnated from an input file, every pair of coordinates itll set to live
    uint32_t rows;
    uint32_t cols;
    while (fscanf(infile, "%u %u\n", &rows, &cols) == 2) { // scan the rest of the lines.
        if (rows < uv_rows(u) && cols < uv_cols(u)) {
	    uv_live_cell(u, rows, cols);
        } 
	else {
            return false;
        }
    }
    /*
    for (rows = 0; rows < uv_rows(u); rows++) { 
        printf("test pop b\n");
	for (cols = 0; cols < uv_cols(u); cols++) {
            if (uv_get_cell(u, rows, cols) == false) {
                uv_dead_cell(u, rows, cols);
            }
        }
    }*/
    return true;
}

// torodial previous helper function
uint32_t toroidal_prev(uint32_t n, uint32_t i) {
    return (i + n - 1) % n;
}

// toroidal next helper function
uint32_t toroidal_next(uint32_t n, uint32_t i) {
    return (i + 1) % n;
}

// the census function counts the number of live adjacent neighbors there are
uint32_t uv_census(Universe *u, uint32_t r, uint32_t c) {
    uint32_t n = 0;
    uint32_t i = 1;
    uint32_t d = 0; // dead neighbor counter
    for (i = 1; i < 8; i++) {
        if (u->toroidal == false && i <= 8) { // if the universe does not wrap around and
            while (i == 1) { // while the increment is on the first neighbor (to the right of [r,c])
                c += 1; // c goes to c + 1, go to the right side neighbor
                //i += 1; // increase the increment by one
                if (uv_get_cell(u, r, c) == false) {
                    d += 1; // increase the dead cell count
                    i += 1; // increase the increment by one
                    //printf("1 = dead\n");
                }
                if (uv_get_cell(u, r, c) == true) { // if the right side neighbor is alive
                    n += 1; // increase the neighbor count
                    i += 1; // increase the increment by one
                    //printf("1 = alive\n");
                }
            }
            while (i == 2) { // while the increment is on the second neighbor (bottom left diagonal)
                r += 1; // r goes to r + 1, go to the bottom left diagonal neighbor
                //i += 1; // increase the increment by one
                if (uv_get_cell(u, r, c) == false) {
                    d += 1; // increase the dead cell count
                    i += 1; // increase the increment by one; move on to the next neighbor
                    //printf("2 = dead\n");
                }
                if (uv_get_cell(u, r, c) == true) { // if the bottom left diagonal neighbor is alive
                    n += 1; // increase live neighbor count
                    i += 1; // increase the incrment count; move on to the next neighbor
                    //printf("2 = alive\n");
                }
            }
            while (
                i
                == 3) { // while the increment is on the third neighbor (bottom middle, right below [r,c])
                c -= 1; // c + 1 goes to c, go to the bottom middle neighbor
                //i += 1; // increase the increment by one
                if (uv_get_cell(u, r, c) == false) {
                    d += 1; // increase the dead cell count
                    i += 1; // increase the increment by one; move on to the next neighbor
                    //printf("3 = dead\n");
                }
                if (uv_get_cell(u, r, c) == true) { // if the bottom middle neighbor is alive
                    n += 1; // increase the live neighbor count
                    i += 1; // increase the increment by one; move on to the next neighbor
                    //printf("3 = alive\n");
                }
            }
            while (i == 4) { // while the increment is on the forth neighbor (bottom right diagonal)
                c -= 1; // c goes to c - 1, go to the bottom right diagonal neighbor
                //i += 1; // increase the increment by one
                if (uv_get_cell(u, r, c) == false) {
                    d += 1; // increase the dead cell count
                    i += 1; // increase the increment by one; move on to the next neighbor
                    //printf("4 = dead\n");
                }
                if (uv_get_cell(u, r, c)
                    == true) { // if the bottom right diagonal neighbor is alive
                    n += 1; // increase the live neighbor count
                    i += 1; // increase the increment by one; move on to the next neighbor
                    //printf("4 = alive\n");
                }
            }
            while (i == 5) { // while the increment is on the fifth neighbor (left side neighbor)
                r -= 1; // r + 1 goes to r; go to the left side neighbor
                //i += 1; // increase the increment by one;
                if (uv_get_cell(u, r, c) == false) {
                    d += 1; // increase the dead cell count
                    i += 1; // increase the increment by one; move on to the next neighbor
                    //printf("5 = dead\n");
                }
                if (uv_get_cell(u, r, c) == true) { // if the left side neighbor is alive
                    n += 1; // increase the live neighbor count
                    i += 1; // increase the increment by one; move on to the next neighbor
                    //printf("5 = alive\n");
                }
            }
            while (i == 6) { // while the increment is on the sixth neighbor (top right diagonal)
                r -= 1; // r goes to r - 1; go to the top right diagonal neighbor
                //i += 1; // increase the increment by one
                if (uv_get_cell(u, r, c) == false) {
                    d += 1; // increase the dead cell count
                    i += 1; // increase the increment by one; move on to the next neighbor
                    //printf("6 = dead\n");
                }
                if (uv_get_cell(u, r, c) == true) { // if the top right diagonal neighbor is alive
                    n += 1; // increase the live neighbor count
                    i += 1; // increase the increment by one; move on to the next neighbor
                    //printf("6 = alive\n");
                }
            }
            while (
                i
                == 7) { // while the increment is on the sixth neighbor (top middle, right above [r, c])
                c += 1; // c - 1 goes to c; go to the top middle neighbor
                //i += 1; // increase the increment by one
                if (uv_get_cell(u, r, c) == false) {
                    d += 1; // increase the dead cell count
                    i += 1; // increase the increment by one; move on to the next neighbor
                    //printf("7 = dead\n");
                }
                if (uv_get_cell(u, r, c) == true) { // if the top middle neighbor is alive
                    n += 1; // increase the live neighbor count
                    i += 1; // increase the increment by one; move on to the next neighbor
                    //printf("7 = alive\n");
                }
            }
            while (i == 8) { // while the increment is on the eight neighbor (top left diagonal)
                c += 1; // c goes to c + 1; go to the top left diagonal neighbor
                //i += 1; // increase the increment by one
                if (uv_get_cell(u, r, c) == false) {
                    d += 1; // increase the dead cell count
                    i += 1; // increase the increment by one; move on to the next neighbor
                    //printf("8 = dead\n");
                }
                if (uv_get_cell(u, r, c) == true) { // if the top left diagonal neighbor is alive
                    n += 1; // increase the live neighbor count
                    i += 1; // increase the increment by one; move on to the next neighbor
                    //printf("8 = alive\n");
                }
            }
        }
        // BEGIN TOROIDAL
        else {
            while (i == 1) { // while the increment is on the first neighbor (to the right of [r,c])
                toroidal_next(uv_cols(u), c); // c goes to c + 1, go to the right side neighbor
                i += 1; // increase the increment by one
                if (uv_get_cell(u, r, c) == true) { // if the right side neighbor is alive
                    n += 1; // increase the neighbor count
                }
            }
            while (i == 2) { // while the increment is on the second neighbor (bottom left diagonal)
                toroidal_next(
                    uv_rows(u), r); // r goes to r + 1, go to the bottom left diagonal neighbor
                i += 1; // increase the increment by one
                if (uv_get_cell(u, r, c) == true) { // if the bottom left diagonal neighbor is alive
                    n += 1; // increase live neighbor count
                }
            }
            while (
                i
                == 3) { // while the increment is on the third neighbor (bottom middle, right below [r,c])
                toroidal_prev(uv_cols(u), c); // c + 1 goes to c, go to the bottom middle neighbor
                i += 1; // increase the increment by one
                if (uv_get_cell(u, r, c) == true) { // if the bottom middle neighbor is alive
                    n += 1; // increase the live neighbor count
                }
            }
            while (i == 4) { // while the increment is on the forth neighbor (bottom right diagonal)
                toroidal_prev(
                    uv_cols(u), c); // c goes to c - 1, go to the bottom right diagonal neighbor
                i += 1; // increase the increment by one
                if (uv_get_cell(u, r, c)
                    == true) { // if the bottom right diagonal neighbor is alive
                    n += 1; // increase the live neighbor count
                }
            }
            while (i == 5) { // while the increment is on the fifth neighbor (left side neighbor)
                toroidal_prev(uv_rows(u), r); // r + 1 goes to r; go to the left side neighbor
                i += 1; // increase the increment by one
                if (uv_get_cell(u, r, c) == true) { // if the left side neighbor is alive
                    n += 1; // increase the live neighbor count
                }
            }
            while (i == 6) { // while the increment is on the sixth neighbor (top right diagonal)
                toroidal_prev(
                    uv_rows(u), r); // r goes to r - 1; go to the top right diagonal neighbor
                i += 1; // increase the increment by one
                if (uv_get_cell(u, r, c) == true) { // if the top right diagonal neighbor is alive
                    n += 1; // increase the live neighbor count
                }
            }
            while (
                i
                == 7) { // while the increment is on the sixth neighbor (top middle, right above [r, c])
                toroidal_next(uv_cols(u), c); // c - 1 goes to c; go to the top middle neighbor
                i += 1; // increase the increment by one
                if (uv_get_cell(u, r, c) == true) { // if the top middle neighbor is alive
                    n += 1; // increase the live neighbor count
                }
            }
            while (i == 8) { // while the increment is on the eight neighbor (top left diagonal)
                toroidal_next(
                    uv_cols(u), c); // c goes to c + 1; go to the top left diagonal neighbor
                i += 1; // increase the increment by one
                if (uv_get_cell(u, r, c) == true) { // if the top left diagonal neighbor is alive
                    n += 1; // increase the live neighbor count
                }
            }
        }
    }
    return n;
    //return d;
}

void uv_print(Universe *u, FILE *outfile) {
    for (uint32_t r = 0; r < uv_rows(u); r++) { // 0 was 1 and < was <=
        for (uint32_t c = 0; c < uv_cols(u); c++) { // 0 was 1 and < was <=
            if (uv_get_cell(u, r, c) == false) {
                fprintf(outfile, ".");
            } else {
                fprintf(outfile, "o");
            }
        }
        fprintf(outfile, "\n");
    }
}
