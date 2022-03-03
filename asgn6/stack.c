#include "stack.h"
#include "node.h"
#include "pq.h"
#include "code.h"
#include "defines.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>

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

struct Stack {
    uint32_t top;
    uint32_t capacity;
    Node **items;
};

Stack *stack_create(uint32_t capacity) {
    // The constructor for a stack.
    // The maximum number of nodes the stack can hold is specified by capacity.
    Stack *s = (Stack *) malloc(sizeof(Stack));
    if (s != NULL) {
        s->top = 0;
        s->capacity = capacity;
        s->items = (Node **) calloc(s->capacity, sizeof(Node *));
        if (s->items == NULL) {
            free(s);
            s = NULL;
        }
    }
    return s;
}

void stack_delete(Stack **s) {
    // The destructor for a stack.
    // Remember to set the pointer to NULL after you free the memory allocated by the stack.
    free(*s);
    *s = NULL;
}

bool stack_empty(Stack *s) {
    // Returns true if the stack is empty and false otherwise. 
    return s->top == 0;
}

bool stack_full(Stack *s) {
    // Returns true if the stack is full and false otherwise. 
    return s->top == s->capacity;
}

uint32_t stack_size(Stack *s) {
    // Returns the number of nodes in the stack.
    return s->top;
}

bool stack_push(Stack *s, Node *n) {
    // Pushes a node onto the stack.
    // Returns false if the stack is full prior to pushing the node.
    // Returns true otherwise to indicate the successful pushing of a node.
    if (stack_full(s)) {
        return false;
    }
    s->items[s->top] = n;
    s->top += 1;
    return true;
}

bool stack_pop(Stack *s, Node **n) {
    // Pops a node off the stack, passing it back through the double pointer n.
    // Returns false if the stack is empty prior to popping a node.
    // Returns true otherwise to indicate the successful popping of a node.
    if (stack_empty(s)) {
        return false;
    }
    s->top -= 1;
    *n = s->items[s->top];
    return true; 
}

void stack_print(Stack *s) {
    // A debug function to print the contents of a stack.
    printf("IGNORE: %u", s->top);
} 
