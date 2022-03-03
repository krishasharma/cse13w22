#include "defines.h"
#include "code.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

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

Code code_init(void) {
    // This function will not require any dynamic memory allocation.
    // You will simply create a new Code on the stack, setting top to 0, and zeroing out the array of bits, bits.
    // The initialized Code is then returned.
    Code c;
    c.top = 0;
    return c;
}

uint32_t code_size(Code *c) {
    // Returns the size of the Code, which is exactly the number of bits pushed onto the Code.
    return c->top;
}

bool code_empty(Code *c) {
    // Returns true if the Code is empty and false otherwise.
    if (c->top == 0) {
        return true;
    } else {
        return false;
    }
}

bool code_full(Code *c) {
    // Returns true if the Code is full and false otherwise.
    // The maximum length of a code in bits is 256, which is defined using the macro ALPHABET.
    if (c->top == ALPHABET) {
        return true;
    } else {
        return false;
    }
}

bool code_set_bit(Code *c, uint32_t i) {
    // Sets the bit at index i in the Code, setting it to 1.
    // If i is out of range, return false.
    // Otherwise, return true to indicate success.
    if (i > ALPHABET / 8 || i == 0) {
        return false;
    } else {
        c->bits[i / 8] |= (1 << (i % 8));
        return true;
    }
}

bool code_clr_bit(Code *c, uint32_t i) {
    // Clears the bit at index i in the Code, clearing it to 0.
    // If i is out of range, return false.
    // Otherwise, return true to indicate success.
    if (i > ALPHABET / 8 || i == 0) {
        return false;
    } else {
        c->bits[i / 8] &= ~(1 << (i % 8));
        return true;
    }
}

bool code_get_bit(Code *c, uint32_t i) {
    // Gets the bit at index i in the Code.
    // If i is out of range, or if bit i is equal to 0, return false.
    // Return true if and only if bit i is equal to 1.
    if (i > ALPHABET / 8 || i == 0) {
        return false;
    } else {
        if ((c->bits[i / 8] & (1 << (i % 8))) == 1) {
            return true;
        }
    }
    return 0;
}

bool code_push_bit(Code *c, uint8_t bit) {
    // Pushes a bit onto the Code. The value of the bit to push is given by bit.
    // Returns false if the Code is full prior to pushing a bit.
    // Returns true otherwise to indicate the successful pushing of a bit.
    if (code_full(c) == true) {
        return false;
    } else {
        c->bits[c->top] = bit; // CITE: Professor Long's Lecture_10_Slides
        c->top += 1;
        return true;
    }
}

bool code_pop_bit(Code *c, uint8_t *bit) {
    // Pops a bit off the Code. The value of the popped bit is passed back with the pointer bit.
    // Returns false if the Code is empty prior to popping a bit.
    // Returns true otherwise to indicate the successful popping of a bit.
    if (code_empty(c) == true) {
        return false;
    }
    c->top -= 1;
    *bit = c->bits[c->top]; // CITE: Professor Long's Lecture_10_Slides
    return true;
}

void code_print(Code *c) {
    // A debug function.
    // Helps you verify whether or not bits are pushed onto and popped off a Code correctly.
    for (uint32_t i = 0; i < ALPHABET / 8; i += 1) {
        printf("index i: %d\n", i);
        printf("bit value at i: %u\n", c->bits[i]);
    }
}
