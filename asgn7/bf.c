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
#include "bf.h"

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

struct BloomFilter {
    uint64_t primary[2]; // primary hash function salt
    uint64_t secondary[2]; // secondary hash function salt
    uint64_t tertiary[2]; // tertiary hash function salt
    BitVector *filter;
};

BloomFilter *bf_create(uint32_t size) {
    // The constructor for a Bloom filter. 
    // The primary, secondary, and tertiary salts that should be used are provided in salts.h. 
    BloomFilter *bf
        = (BloomFilter *) malloc(sizeof(BloomFilter)); // allocate memory for the bloom filter
    if (bf == NULL) { // if memory could not be allocated for the bloom filter 
        return NULL; // return NULL
    }
    BitVector *filter = bv_create(size); // create a bit vector
    if (filter == NULL) { // if the bit vector equals NULL
        free(bf); // free the bloom filter
        bf = NULL; // set the bloom filter equal to NULL
        return NULL; 
    }
    bf->filter = filter;
    bf->primary[0] = SALT_PRIMARY_LO;
    bf->primary[1] = SALT_PRIMARY_HI;
    bf->secondary[0] = SALT_SECONDARY_LO;
    bf->secondary[1] = SALT_SECONDARY_HI;
    bf->tertiary[0] = SALT_TERTIARY_LO;
    bf->tertiary[1] = SALT_TERTIARY_HI;
    return bf;
}

void bf_delete(BloomFilter **bf) {
    // The destructor for a Bloom filter.
    bv_delete(&(*bf)->filter); // delete the bit vector
    free(*bf); // free the bloom filter
    *bf = NULL; // set the pointer to the bloom filter equal to NULL
}

uint32_t bf_size(BloomFilter *bf) {
    return bv_length(bf->filter);
}

void bf_insert(BloomFilter *bf, char *word) {
    // Takes word and inserts it into the Bloom filter.
    uint32_t index1 = hash(bf->primary, word); // hash the word with the primary salt
    index1 = index1 % bf_size(bf); // mod by the size of the bloom filter
    uint32_t index2 = hash(bf->secondary, word); // hash the word with the secondary salt
    index2 = index2 % bf_size(bf); // mod by the size of the bloom filter
    uint32_t index3 = hash(bf->tertiary, word); // hash the word with the tertiary salt
    index3 = index3 % bf_size(bf); // mod by the size of the bloom filter
    bv_set_bit(bf->filter, index1); // sets the bits at index1 to 1
    bv_set_bit(bf->filter, index2); // sets the bits at index2 to 1
    bv_set_bit(bf->filter, index3); // sets the bits at index3 to 1
}

bool bf_probe(BloomFilter *bf, char *word) {
    // Probes the Bloom filter for word.
    uint32_t count = 0;
    uint32_t index1 = hash(bf->primary, word); // hash the word with the primary salt
    index1 = index1 % bf_size(bf); // mod by the size of the bloom filter
    uint32_t index2 = hash(bf->secondary, word); // hash the word with the secondary salt
    index2 = index2 % bf_size(bf); // mod by the size of the bloom filter
    uint32_t index3 = hash(bf->tertiary, word); // hash the word with the tertiary salt
    index3 = index3 % bf_size(bf); // mod by the size of the bloom filter
    if (bv_get_bit(bf->filter, ind1) == true) { // if the value of the bit at index1 is 1
        count += 1;
    }
    if (bv_get_bit(bf->filter, ind2) == true) { // if the value of the bit at index2 is 1
        count += 1;
    }
    if (bv_get_bit(bf->filter, ind3) == true) { // if the value of the bit at index3 is 1
        count += 1;
    }
    if (count == 3) {
        return true;
    } else if (count > 3) {
        printf("probe failed");
    }
    return false;
}

void bf_print(BloomFilter *bf) {
    // A debug function to print out the bits of a Bloom filter.
    bv_print(bf->filter);
}
