#include <stdlib.h>
#include <stdio.h>
#include "universe.h"
#include <unistd.h>
#include <inttypes.h>
#include <stdbool.h>
#include <ncurses.h>

#define DELAY 50000

int main(int argc, char **argv) {
    uint32_t rows;
    uint32_t cols;
    bool toro = false;
    //FILE *fill = fopen("life.txt", "r"); // infile was fill
    uint32_t generation = 0;
    int opt = 0;

    bool l_t = false;
    bool l_s = false;
    bool l_n = false;
    bool l_i = false;
    bool l_o = false;

    FILE *in = fopen("stdin", "r");
    FILE *out = fopen("stdout", "r");

    while ((opt = getopt(argc, argv, "tsn:i:o:")) != -1) {
        switch (opt) {
        // -t specify that the Game of Life is to be played on a toroidal universe.
        case 't':
            l_t = true;
            toro = true;
            break;
        // -s silences ncurses, enabling this option means that nothing should be dispalyed by ncurses.
        case 's': l_s = true; break;
        // -n generations, specify the number of generations that the universe goes through. the default number of generations is 0.
        case 'n':
            l_n = true;
            generation = strtod(optarg, NULL);
            break;
        // -i input, specify the input file to read in order to populate the universe. by default the input should be stdin.
        case 'i':
            l_i = true;
            in = fopen(optarg, "r");
            break;
        // -o output, specify the output file to print the final state of the universe to. by default the output should be stdout.
        case 'o':
            l_o = true;
            out = fopen(optarg, "w");
            break;
        }
    }

    fscanf(in, "%d %d", &rows, &cols);
    Universe *uniA = uv_create(rows, cols, toro);
    Universe *uniB = uv_create(rows, cols, toro);
    Universe *uniC = uv_create(rows, cols, toro);
    uv_populate(uniA, in);
    fclose(in);

    initscr();
    curs_set(FALSE);

    for (uint32_t i = 0; i <= generation; i++) {
        clear();
        for (rows = 0; rows < uv_rows(uniA); rows++) {
            for (cols = 0; cols < uv_cols(uniA); cols++) {
                uint32_t censusval = uv_census(uniA, rows, cols);
                if ((uv_get_cell(uniA, rows, cols) == true)
                    && ((censusval == 2) || (censusval == 3))) {
                    uv_live_cell(uniB, rows, cols);
                    mvprintw(rows, cols, "o");
                } else if ((uv_get_cell(uniA, rows, cols) == false) && (censusval == 3)) {
                    uv_dead_cell(uniB, rows, cols);
                    mvprintw(rows, cols, "o");
                } else {
                    uv_dead_cell(uniB, rows, cols);
                    mvprintw(rows, cols, ".");
                }
                uniC = uniA;
                uniA = uniB;
                uniB = uniC;
            }
        }
        refresh();
        usleep(DELAY);
    }
    endwin();
    uv_print(uniA, out);
    uv_delete(uniA);
    uv_delete(uniB);
    uv_delete(uniC);
    fclose(out);

    // generations for loop pusedocode Audrey Ostrom tutoring session
    // three for loops both universes are the same size, A is populated, B starts empty
    // for (int i = 0; ___ ; i++) {
    //    for (rows) {
    //        for (cols) {
    //            take a census; feed through uv_census
    //            check the results and see how many neighbors its has
    //            mvprintw(ROW, col, "o"); // where this goes depends on whether the cell is marked as live or dead
    //            make the cells in univese B dead or alive based on the neighbors uv_live uv_get uv_dead
    //        }
    //    }
    //    refresh();
    //    usleep(DELAY);
    // }

    //uint32_t v = uv_census(uniA, 0, 0);
    //printf("%d\n", v);
    return 0;
}
