#include "randstate.h"
#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Please Note:
// The implemented code is based off of pseudocode provided by the Professor in the assignment PDF
// There is also high level pseudocode collaboration with my sister Twisha Sharma (tvsharma)
// Audrey is cited in randstate.c as she provided pseudocode for it during her tutoring section 
// on 02_09_2022
// Eugene is cited in numtheory.c for the pseudocode for the pow_mod and the is_prime functions 
// given during his lab section on 02_04_2022
// Eugene is also cited in numtheory.c make_prime specifically for for the idea of 
// adding 2^bits + the random num generated from urandomb that caps at user input bits given
// Eugene is once again cited in keygen.c for explaining how to properly implement fchmod() and fileno() 
// in keygen.c during his office hours on 02_16_2022
// Omar is cited in numtheory.c for explaining how to implement the mpz functions from the GMP library
// Brian is cited in rsa.c specifically in rsa_make_pub for explaining how to generate a random number
// in the range specified in the asgn_5 PDF 

gmp_randstate_t state;


void randstate_init(uint64_t seed) {
    // initializes a global random state named state with a Mersenne Twister algorithm 
    // using seed as the random seed 
    // call srandom() using this seed as well 
    // call gmp_randinit_mt() and gmp_randseed_ui()
    // should be two or three lines MAX 
    gmp_randinit_mt(state);
    gmp_randseed_ui(state, seed);
    srandom(seed);
}


void randstate_clear(void) {
    // calls and frees all memory used by the inatilized global random state, state
    // should be a single call to gmp_randclear()
    // should be two or three lines MAX 
    gmp_randclear(state);
}
