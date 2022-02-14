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
   
    // test for pow_mod 
    /*mpz_t out, base, exponent, modulus;
    mpz_inits(out, base, exponent, modulus, NULL);
    mpz_set_ui(base, 5);
    mpz_set_ui(exponent, 9);
    mpz_set_ui(modulus, 20);
    pow_mod(out, base, exponent, modulus);
    gmp_printf("out is: %Zd\n", out);*/    
    
    // test for mod_inverse 
    /*mpz_t i; 
    mpz_t a; 
    mpz_t n; 
    mpz_inits(i, a, n, NULL);
    mpz_set_ui(a, 7);    
    mpz_set_ui(n, 32);
    mod_inverse(i, a, n);
    gmp_printf("i is: %Zd\n", i);*/

    mpz_t p;
    mpz_init(p);
    uint64_t bits = 20;
    uint64_t iters = 50;
    make_prime(p, bits, iters);
    gmp_printf("p is: %Zd\n", p);

    // test for is_prime 
    /*mpz_t n; 
    mpz_init(n); 
    mpz_set_ui(n, 17);
    uint64_t iters = 50;
    if ((is_prime(n, iters)) == true) {
        gmp_printf("%Zd is prime\n", n);
    }*/
    
    // secondary test for is_prime
    /*for(int i = 0; i < 100; i++) { 
        if((is_prime(n, iters)) == true) {
            gmp_printf("%Zd is prime\n", n);
            mpz_add_ui(n, n, 1);
        }
        if((is_prime(n, iters)) == false) {
            //gmp_printf("%Zd is not prime\n", n);
            mpz_add_ui(n, n, 1); 
        }  
    }
    gcd(d, a, b);
    */

    mpz_clears(p, NULL);

    //mpz_clears(out, base, exponent, modulus, NULL);
    
    //mpz_clears(i, a, n, NULL);
    
    //mpz_clears(n, NULL);

    randstate_clear();
;
}
