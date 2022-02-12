#include <randstate.h>
#include <gmp.h>
#include <stdio.h>

// randstate.c and numbtheory.c at the same time
// rsa.c
// keygen.c
// encrypt.c
// decrypt.c 

struct state {
    gmp_randstate_t state;
    uint64_t seed;
}

void randstate_init(uint64_t seed) {
    // initializes a global random state named state with a Mersenne Twister algorithm 
    // using seed as the random seed 
    // call srandom() using this seed as well 
    // call gmp_randinit_mt() and gmp_randseed_ui()
    // should be two or three lines MAX 
    //srandom(seed);
    gmp_randinit_mt(state);
    gmp_randseed_ui(state, seed);
    //gmp_randinit_mt(state);
}

void randstate_clear(void) {
    // calls and frees all memory used by the inatilized global random state, state
    // should be a single call to gmp_randclear()
    // should be two or three lines MAX 
    gmp_randclear(state);
}
