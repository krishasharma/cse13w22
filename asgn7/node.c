#include "node.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

Node *node_create(char *word) {
    // The constructor for a node. 
    Node *n = (Node *) malloc(sizeof(Node)); // allocate memory for the node
    n->word = strdup(word); // function that returns a pointer to the string decleration
    n->count = 0; 
    return n;
}

void node_delete(Node **n) {
    // The destructor for a node.
    free((*n)->word); // free the memory allocated for the word
    (*n)->word = NULL; // set the pointer to the memory allocated for the word to NULL
    free(*n); // free the node
    *n = NULL; // set the pointer to the node equal to NULL
}

void node_print(Node *n) {
    // A debug function to print out the contents of a node.
    printf("words: %s\n", n->word); // prints out the contents of a node
}
