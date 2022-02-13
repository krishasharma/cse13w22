#include "numtheory.h"
#include "randstate.h"
#include <gmp.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <gmp.h>


// Please Note: 
// The implemented code is based off of pseudocode provided by the Professor in the assignment PDF
// There is also high level pseudocode collabration with my sister Twisha Sharma (tvsharma)
// Eugene is cited in numtheory.c for the pusedocode for the pow_mod and the is_prime functions
// Omar is cited in numtheory.c for explaining how to correctly implement the mpz functions from the GMP library


/*void pow_mod(int64_t out, int64_t base, int64_t exponent, int64_t modulus) {
    // initalize some variables to hold the initial values given by the parameters 
    // while loop (while d > 0) is covered by:
    // compare, multiply, mod, division function 
    // while d is odd (which is another function in

    int64_t v = 1;
    int64_t p = base;
    while (exponent > 0) {
        if ((exponent % 2) == 1) { // anything with a remiander of one is odd or ((exponent & 1) == 1)
            v = (v * p) % modulus;
        }
        p = (p * p) % modulus;
        exponent = exponent / 2; //tdiv or fdiv for mpz division.
        //exponent >>= 1; 
    }
    out = v;
    //return out;
    printf("out is: %ld\n", out);
}*/

void pow_mod(mpz_t out, mpz_t base, mpz_t exponent, mpz_t modulus) {
    mpz_t v;
    mpz_t p;
    mpz_t e;
    mpz_t vp;
    mpz_t pp;
    mpz_inits(v, p, e, vp, pp, NULL);
    mpz_set_ui(v , 1);
    mpz_set(p, out); //mpz_t p <- mpz_t out; // ???
    mpz_mul(vp, v, p);
    mpz_mul(pp, p, p);
    while (mpz_cmp_ui(base, 0) == 1) {
        if (mpz_odd_p(base) != 0) {
            mpz_mod(v, vp, modulus); // v = (v * p) % modulus
        }
        mpz_mod(p, pp, modulus); // p = (p * p) % modulus 
        mpz_fdiv_q_ui(base, base, 2);
	mpz_set(exponent, e);
    }
    mpz_set(out, v);
    mpz_clears(v, p, e, vp, pp, NULL);
}



/*bool is_prime(int64_t n, int64_t iters) {
    printf("n = %ld\n", n);
    if(n == 2) {
        printf("test 0\n");
        return true;
    }
    if(n % 2 == 1) { // check that n is odd
        printf("n = %ld\n", n);
        int64_t n_initial = n - 1; // save n-1 to another variable to use as a check
        printf("n_initial = %ld\n", n_initial);
        int64_t n_clone = n; // this is the n-1 variable you can compute with
        int64_t r;
        int64_t s;
        printf("test 1\n");
        for(s = 0; s <= n_initial ; s++) { // loop - limit at pow(2, s) *n == nminus
            printf("test 2\n");
            n_initial = n_clone / 2; // calculate the remainder by dividing by two until the check underneath is satisfied
            printf("n_inital = %ld\n", n_initial);
            n_clone = n_initial;
            printf("n_clone = %ld\n", n_clone);
            printf("n = %ld\n", n);
            printf("s = %ld\n", s);
            if(((2^s * n_initial)  == n_initial) && n_initial % 2 == 1) { // check if the equation is satisfied
                r = n_initial; // set the remainder
                printf("s = %ld\n", s);
                printf("r = %ld\n", r);
            }
        }
        srandom(time(0));
        for(int64_t i = 1; i <= iters; i ++) {
            int64_t lower = 2;
            int64_t upper = n - 2;
            int64_t a = (random() % (lower - upper + 1)) + lower; // CITE: Eugene section 02_04_2022 & pseduocode collabration w/ tvsharma
            int64_t y = 0;
            pow_mod(y, a, r, n);
            if(y != 1 && y != (n - 1)) {
                int64_t j = 1;
                while(j <= (s - 1) && y != (n - 1)) {
                    pow_mod(y, y, 2, n);
                    if(y == 1) {
                        return false;
                    }
                    j = j + 1;
                }
                if(y != (n - 1)) {
                    return false;
                }
            }
        }
        return true;
    }
    return false;
}*/

bool is_prime(mpz_t n, uint64_t iters) {
    mpz_t n_clone;
    mpz_t n_1; // var to hold n - 1
    mpz_t s;
    mpz_t r;
    mpz_t sminus; // var to hold s - 1 
    mpz_inits(n_clone, n_1, r, s, sminus, NULL);
    mpz_t a;
    mpz_t y;
    mpz_t j;
    mpz_t jadd; // var to hold j + 1
    mpz_t upperrange;
    mpz_t two; // var to hold the number 2 
    mpz_inits(a, y, j, jadd, upperrange, two, NULL);
    
    mpz_set_ui(two, 2);
    mpz_set(n_clone, n); // n_clone = n 
    mpz_sub_ui(n_1, n, 1); // n_1 = n - 1
    //gmp_randstate_t state; // sets up a random state 
    if(mpz_odd_p(n) != 0) {
        for (mpz_set_ui(s, 0); mpz_even_p(n_clone); mpz_add_ui(s, s, 1)) {
            mpz_fdiv_q_ui(n_1, n_clone, 2); 
            mpz_set(n_clone, n_1);
        }
        mpz_set(r, n_clone);
        //gmp_randinit_default(state); // srandom(time(0))
    }
    for (uint64_t i = 1; i <= iters; i++) {
	mpz_sub_ui(upperrange, n, 3);
        mpz_urandomm(a, state, n_1); // choose random a from range {2,..., n - 2)
        mpz_add_ui(a, a, 2);
	pow_mod(y, a, r, n);
        if ((mpz_cmp_ui(y, 1) != 0) && (mpz_cmp(y, n_1) != 0)) {
	    mpz_set_ui(j, 1);
	    while ((mpz_cmp(j, sminus) != 1) && (mpz_cmp(y, n_1) != 0)) { // while j <= s-1 & y != n - 1
	        pow_mod(y, y, two, n);
		if ((mpz_cmp_ui(y, 1) == 1)) {
		    mpz_clears(n_clone, n_1, r, s, sminus);
		    mpz_clears(a, y, j, jadd, upperrange, two);
	            return false;
		}
		mpz_add_ui(jadd, j, 1);
	    }
	    if (mpz_cmp(y, n_1) != 0) {
                mpz_clears(n_clone, n_1, r, s, sminus);
		mpz_clears(a, y, j, jadd, upperrange, two);
	        return false;
	    }
	}
    }
    mpz_clears(n_clone, n_1, r, s, sminus);
    mpz_clears(a, y, j, jadd, upperrange, two);
    return true; 
}



/*void make_prime(int64_t p, uint64_t bits, uint64_t iters) {
    break;
}*/

/*void make_prime(mpz_t p, uint64_t bits, uint64_t iters) {
    // generates a new prime number stored in p
    // the generated prime should be at least bits number or bits long
}*/



/*void gcd(int64_t d, int64_t a, int64_t b) {
    // computed the greatest common divisor of a and b, storing the value in d
    while (b != 0) { // later change condition to mpz_cmp_ui(b, 0) == false
        int64_t t = b;
        b = a % d;
        a = t; 
    }
    return a;
}*/


void gcd( mpz_t d, mpz_t a, mpz_t b) {
    mpz_t t;
    mpz_inits(t, NULL);    
    while(mpz_cmp_ui(b, 0) == 1 || mpz_cmp_ui(b, 0) == -1) { // while the compare function does not return 0
        mpz_set(t, b);
        mpz_mod(b, a, b); //b= a mod b 
        mpz_set(a, t);
    }
    mpz_set(d, a);
    mpz_clears(t, NULL);         
}



/*void mod_inverse(int64_t i, int64_t a, int64_t n) {
    int64_t r = n;
    int64_t rprime = a;
    int64_t t = 0;
    int64_t tprime = 1;
    int64_t q;
    while (rprime != 0) {
        q = r / rprime;
	r = rprime;
	rprime = r - q * rprime;
        t = tprime;
        tprime = t - q * tprime;	
    }
    if (r > 1) {
	i = 0; // if there is no inverse, set i to zero
    }
    if (t < 0) {
        t = t + n;
    }
    return t;     
}*/

/*
void mod_inverse(mpz_t i, mpz_t a, mpz_t n) {
    // computes the inverse i of a modulo n 
    // if there is no mod inverse, set i to zero 
}*/
