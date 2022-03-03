#include "huffman.h"
#include "node.h"
#include "code.h"
#include "pq.h"
#include "stack.h"
#include "io.h"
#include "defines.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>
#include <sys/stat.h>
#include "defines.h"

// Please Note: The implemented code is based off of pseudocode provided by the Professor in the assignment PDF
// There is also high level pseudocode collaboration with my sister Twisha Sharma (tvsharm)
// Eugene is cited throughout the asgn for his explanation during his lab section on 02_18_2022.
// Eugene explained how to set up the assignment for huffman coding as well as explained how to properly begin
// each step of the assignment.
// Audrey is cited for her tutoring session on 02_25_2022 when she helped look over my huffman.c and node.c.
// Audrey also helped me fix syntax error in stack.c during her tutoring session on 03_02_2022
// She specifically helped me with stack_pop()
// Ben is cited for helping me with read_bytes and write_bytes during his tutoring session on 03_01_2022
// During his tutoring session he explained how to best implement read_bytes. Ben also looked over my code.c
// Brian is cited for his section on 02_28_2022 when he helped look over my pq.c
// Brian helped to also explain how to proceed with code.c and the best way to go about implementing the functions
// Brian also helped me during his tutoring session on 03_02_2022 by looking over my io.c file and helping me
// fix compilation and syntax errors

int main(int argc, char **argv) {
    int opt = 0;
    bool h = false;
    bool i = false;
    bool o = false;
    bool v = false;
    FILE *infile = stdin; // Default file is stdin
    FILE *outfile = stdout; // Default file is stdout
    
    while ((opt = getopt(argc, argv, "hi:o:v")) != -1) {
        switch (opt) {
        case 'h':
            h = true;
	    // CREDIT: resources repo refrence program 
            printf("SYNOPSIS\n"); 
            printf("   A Huffman encoder.\n");
            printf("   Compresses a file using the Huffman coding algorithm.\n");
            printf("USAGE\n");
            printf("   ./encode [-h] [-i infile] [-o outfile]\n");
            printf("OPTIONS\n");
            printf("   -h             Program usage and help.\n");
            printf("   -v             Print compression statistics.\n");
            printf("   -i infile      Input file to compress.\n");
            printf("   -o outfile     Output of compressed data.\n");
            return 1;
            break;
        case 'i':
            i = true;
            infile = open(optarg, O_RDONLY); // Set infile if specified
            break;
        case 'o':
            o = true;
            outfile = optarg; // Set outfile if specified
            break;
        case 'v':
            v = true;
            break;
        }
    }
    
    uint64_t *histo (uint64_t *) calloc(ALPHABET, sizeof(uint64_t));

    int spc_symb_index = 0;
    if (!i) {
        open(infile, 0_RDONY);
    }
    in_bytes = read_bytes(infile, histo, );
    if (spc_symb_index != 256 && histo[spc_symb_index] != 0) {
        spc_symb_index += 1;
    }
    uint64_t histo[ALPHABET] = {spc_symb_index};

}

