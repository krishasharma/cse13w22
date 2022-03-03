#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "node.h"

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

Node *node_create(uint8_t symbol, uint64_t frequency) {
    // The constructor for a node.
    // Sets the node’s symbol as symbol and its frequency as frequency.
    Node *n = (Node *) malloc(sizeof(Node));
    n->left = NULL; //(Node *)calloc(left, sizeof(Node));
    n->right = NULL; //(Node )calloc(right, sizeof(Node));
    n->symbol = symbol; // set the symbol to symb
    n->frequency = frequency; // set the frequency to freq
    return n;
}

void node_delete(Node **n) {
    // The destructor for a node.
    // Make sure to set the pointer to NULL after freeing the memory for a node.
    free(*n);
    *n = NULL;
}

Node *node_join(Node *left, Node *right) {
    // Joins a left child node and right child node, returning a pointer to a created parent node.
    // The parent node’s left child will be left and its right child will be right.
    // The parent node’s symbol will be ‘$’.
    // The parent node's frequency is the sum of its left child’s frequency and its right child’s frequency.
    uint8_t pnsymbol = '$'; // sets parent node symbol to $
    uint64_t pnfrequency
        = left->frequency + right->frequency; // sets parent node freq oto left freq + right freq
    Node *pn = node_create(pnsymbol, pnfrequency); // create the parent node
    pn->left = left; // sets parent node's left child to left
    pn->right = right; // sets parent node's right child to right
    return pn;
}

void node_print(Node *n) {
    // A debug function to verify that your nodes are created and joined correctly.
    printf("%lu\n", n->frequency); // test debugging tool
    printf("%d\n", n->symbol);
}
