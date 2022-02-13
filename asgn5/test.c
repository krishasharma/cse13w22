#include "numtheory.h"
#include "randstate.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <math.h>
#include <time.h>

// Please Note: 
// The implemented code is based off of pseudocode provided by the Professor in the assignment PDF
// There is also high level pseudocode collabration with my sister Twisha Sharma (tvsharma)
// Eugene is cited in numtheory.c for the pusedocode for the pow_mod and the is_prime functions
// Omar is cited in numtheory.c for explaining how to correctly implement the mpz functions from the GMP library 

int main() {
    uint64_t seed = 10;
    randstate_init(seed);
    mpz_t n;
    mpz_init(n);
    mpz_set_ui(n , 4);
    uint64_t iters = 50;
    if ((is_prime(n, iters)) == true) {
        printf("is prime");
    }
    if ((is_prime(n, iters)) == false) {
        printf("is not prime");
    }
    mpz_clears(n, NULL);
    randstate_clear();
}
