#include <stdlib.h>
#include <stdio.h>
#include "universe.h"
#include <unistd.h>
#include <inttypes.h>
#include <stdbool.h>
#include <ncurses.h>

#define DELAY 50000

// Please Note: The implemented code is based off of pusedocode provided by the Professor in the assignment PDF
// There is also high level pusedocode collabration with my sister Twisha Sharma (tvsharm) 
// The generations for loop is based off of pusedocode provided by Audrey Ostrom 
// The ncurses implementation is based off of pusedocode given in the assignment PDF

int main(int argc, char **argv) {
    uint32_t rows;
    uint32_t cols;
    bool toro = false;
    uint32_t generation = 0;
    int opt = 0;

    bool l_t = false;
    bool l_s = false;
    bool l_n = false;
    bool l_i = false;
    bool l_o = false;

    FILE *in = fopen("stdin", "r");
    FILE *out = fopen("stdout", "r");
    
    // this getopt loop is based off of the example get opt loop Eugene showed during his section for asgn_2 
    while ((opt = getopt(argc, argv, "tsn:i:o:")) != -1) {
        switch (opt) {
        // -t specify that the Game of Life is to be played on a toroidal universe.
        case 't':
            l_t = true;
            toro = true;
            break;
        // -s silences ncurses, enabling this option means that nothing should be dispalyed by ncurses.
        case 's': 
	    l_s = true; 
	    break;
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
    uv_populate(uniA, in);
    fclose(in);

    if (!l_s) {
        initscr();
        curs_set(FALSE);
    }
    
    // this code is based off of pusedocode from Audrey Ostrom's tutoring session on 02_02_2022
    // there was also high level pusedocode collabration with my sister Twisha Sharma (tvsharma) 
    // when attempting to begin coding ncurses and the generations for loop
    for (uint32_t i = 0; i <= generation; i++) { 
 	clear();
        for (rows = 0; rows < uv_rows(uniA); rows++) { 
            for (cols = 0; cols < uv_cols(uniA); cols++) {
                uint32_t censusval = uv_census(uniA, rows, cols);
                if ((uv_get_cell(uniA, rows, cols) == true) && ((censusval == 2) || (censusval == 3))) {
                    uv_live_cell(uniB, rows, cols);
                    if(!l_s) {
			mvprintw(rows, cols, "o");
		    }
                }
		else if ((uv_get_cell(uniA, rows, cols) == false) && (censusval == 3)) {
                    uv_dead_cell(uniB, rows, cols);
                    if (!l_s) {
			mvprintw(rows, cols, "o");
		    }
                } 
		else {
                    uv_dead_cell(uniB, rows, cols);
                    if (!l_s){
			mvprintw(rows, cols, ".");
	            }
                }
                Universe * temp = uniA;
		uniA = uniB;
                uniB = temp;
            }
	    refresh();
            usleep(DELAY);
        }
    }
    endwin();
    uv_print(uniA, out);
    uv_delete(uniA);
    uv_delete(uniB);

    fclose(out);   
    return 0;    

}

