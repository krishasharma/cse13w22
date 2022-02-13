#include "randstate.h"
#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// randstate.c and numbtheory.c at the same time
// rsa.c
// keygen.c
// encrypt.c
// decrypt.c 

// Please Note:
// The below code is based off of pseudocode provided during Audrey's tutoring section on ______

/*struct state {
    gmp_randstate_t state;
    uint64_t seed;
};*/

gmp_randstate_t state;

void randstate_init(uint64_t seed) {
    // initializes a global random state named state with a Mersenne Twister algorithm 
    // using seed as the random seed 
    // call srandom() using this seed as well 
    // call gmp_randinit_mt() and gmp_randseed_ui()
    // should be two or three lines MAX 
    //srandom(seed);
    gmp_randinit_mt(state);
    gmp_randseed_ui(state, seed);
    srandom(seed);
    //gmp_randinit_mt(state);
}

void randstate_clear(void) {
    // calls and frees all memory used by the inatilized global random state, state
    // should be a single call to gmp_randclear()
    // should be two or three lines MAX 
    gmp_randclear(state);
}
