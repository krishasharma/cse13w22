#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include "node.h"
#include "salts.h"
#include "ht.h"
#include "speck.h"
#include "bv.h"

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

struct BitVector {
    uint32_t length;
    uint8_t *vector;
};

BitVector *bv_create(uint32_t length) {
    // The constructor for a bit vector that holds length bits.
    BitVector *bv = (BitVector *) malloc(
        sizeof(BitVector)); // allocate memory for one bit vector of length bits
    if (bv == NULL) {
        return NULL;
    }
    uint8_t *vector = (uint8_t *) calloc(((length + 7) / 8), sizeof(uint8_t));
    if (vector == NULL) {
        free(bv);
        bv = NULL;
        return NULL;
    }
    bv->vector = vector;
    bv->length = length;
    /*if (bv == NULL) {
        return NULL;
    }*/
    return bv;
}

void bv_delete(BitVector **bv) {
    // The destructor for a bit vector.
    free((*bv)->vector);
    (*bv)->vector = NULL;
    free(*bv);
    *bv = NULL;
}

uint32_t bv_length(BitVector *bv) {
    // Returns the length of a bit vector.
    return bv->length;
}

bool bv_set_bit(BitVector *bv, uint32_t i) {
    // Sets the i th bit in a bit vector.
    // If i is out of range, return false.
    // Otherwise, return true to indicate success.
    if (i > (bv->length) || i < 0) {
        return false;
    } else {
        bv->vector[i / 8] |= (0x1 << (i % 8)); // Sets the bit to 1
        return true;
    }
}

bool bv_clr_bit(BitVector *bv, uint32_t i) {
    // Clears the i th bit in the bit vector.
    // If i is out of range, return false.
    // Otherwise, return true to indicate success. 
    if (i > (bv->length) || i < 0) {
        return false;
    } else {
        bv->vector[i / 8] &= ~(0x1 << (i % 8)); // Clear the bit to 0
        return true;
    }
}

bool bv_get_bit(BitVector *bv, uint32_t i) {
    // Returns the i th bit in the bit vector.
    // If i is out of range, return false.
    // Otherwise, return false if the value of bit i is 0 and return true if the value of bit i is 1.
    if (i > (bv->length) || i < 0) {
        return false;
    }
    if (((bv->vector[i / 8] >> i % 8) & 0x1) == 1) { // Checking if a single bit is equal to 1
        return true;
    }
    return false;
}

void bv_print(BitVector *bv) {
    // A debug function to print the bits of a bit vector. 
    uint32_t currentbyte = 0;
    for (currentbyte = 0; currentbyte < bv_length(bv); currentbyte += 1) {
        if (bv_get_bit(bv, currentbyte) == true) {
            printf("1 [%u],\n", currentbyte); // 1 value
        } else {
            printf("0 [%u],\n", currentbyte); // 0 value
        }
    }
}
