#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "ht.h"
#include "speck.h"
#include "bv.h"
#include "bf.h"
#include <regex.h>
#include "parser.h"
#include "text.h"
#include "speck.h"
#include "metric.h"

// Please Note: Professor Long is cited throughout this assignment for providing the pseudocode in the assignment7 PDF document. 
// Professor Long is also cited for the help he gave as Walter Sobchack (Elmer) on discord in the CSE13s - Winter2022 - Professor Long server.
// Throughout this assignment, I had high-level pseudocode collaboration with my sister Twisha Sharma (tvsharma)
// Eugene is cited throughout this assignment for this help with explaining how to properly begin and correctly implement this assignment 
// during his section on 03_04_2022
// Ben is cited for his tutoring session on 03_08_2022
// during it he helped me understand that to access the salt array we should treat it as a pointer because we want to access the whole 
// array, not a specific part of the array.
// Audrey is cited for her tutoring session on 03_09_2022
// during it she helped me understand how to properly delete the hash table as my destructor function was running errors.

int main(int argc, char **argv) {
    int opt = 0;
    bool d = false;
    bool n = false;
    bool k = false;
    bool l = false;
    bool e = false;
    bool m = false;
    bool c = false;
    bool h = false;
    // Default files for the author database and noise file
    FILE *authorfile = lib.db;
    FILE *noisefile = noise.txt;
    int matches = 5;
    int filterwordcount = 100;
    char metric = EUCLIDEAN;
    while ((opt = getopt(argc, argv, "hd:n:k:l:emc")) != -1) {
        switch (opt) {
        case 'h':
            h = true;
            printf("SYNOPSIS\n"); // Credit : resources repo refrence program
            printf("   A Huffman encoder.\n");
            printf("   Compresses a file using the Huffman coding algorithm.\n");
            printf("USAGE\n");
            printf("   ./identify [-h] \n");
            printf("OPTIONS\n");
            printf("   -h             Program usage and help.\n");
            printf("   -d             Specify path to database of author and text. The default is lib.txt\n");
            printf("   -n             Specify path to file of noise words to filter out. The default is noise.txt\n");
            printf("   -k             Specify the number of matches. The default is 5\n");
            printf("   -l             Specify the number of noise word to filter out. The default is 100..\n");
            printf("   -e             Set the distance metric to use as the Euclidean distance.\n");
            printf("   -m             Set the distance metric to use as the Manhattan distance.\n");
            printf("   -c             Set the distance metric to use as the Cosine distance.\n");
            return 1;
            break;
        case 'd':
            d = true;
            authorfile = optarg  // Set author if specified
            break;
        case 'n':
            n = true;
            noisefile = optarg; // Set noise if specified
            break;
        case 'k':
            k = true;
            matches = optarg; // Set the matches if specified 
            break;
        case 'l':
            l = true;
            filterwordcount = optarg; // Set the number of noise words to filter out
            break;
        case 'e':
            e = true;
            break;
        case 'm':
            m = true;
            metric = MANHATTAN; // Set the metric to Manhattan
            break;
        case 'c':
            c = true;
            metric = COSINE // Set the metric to cosine
        }
    }

    Text *text = text_create(stdin, noisefile);
    Text *noise = text_create(text);
    fopen(
}
