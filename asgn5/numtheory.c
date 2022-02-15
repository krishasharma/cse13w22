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
// Audrey is cited in randstate.c as she provided pusedocode for it during her tutoring section 
// on 02_09_2022
// Eugene is cited in numtheory.c for the pusedocode for the pow_mod and the is_prime functions 
// given during his lab section on 02_04_2022
// Eugene is also cited in numtheory.c make_prime specifically for for the idea of 
// adding 2^bits + the random num generated from urandomb that caps at user input bits given
// Omar is cited in numtheory.c for explaining how to implement the mpz functions from the GMP library
// Brian is cited in rsa.c specifically in rsa_make_pub for explaining how to generate a random number
// in the range specificed in the asgn_5 PDF 


void pow_mod(mpz_t out, mpz_t base, mpz_t exponent, mpz_t modulus) {
    mpz_t v;
    mpz_t p;
    mpz_t e; // var to copy exponent
    mpz_t vp; // var to store (v * p)
    mpz_t pp; // var to store (p * p)
    mpz_inits(v, p, e, vp, pp, NULL);
    mpz_set(e, exponent); // e = exponent
    mpz_set_ui(v, 1); // v = 1
    mpz_set(p, base); // set p to the base, p now holds any base val 
    
    while (mpz_cmp_ui(e, 0) == 1) {
        if (mpz_odd_p(e) != 0) {
	    mpz_mul(vp, v, p);
            mpz_mod(v, vp, modulus); // v = (v * p) % modulus
        }
        mpz_mul(pp, p, p);
	mpz_mod(p, pp, modulus); // p = (p * p) % modulus 
        mpz_fdiv_q_ui(e, e, 2);
    }

    mpz_set(out, v);
    mpz_clears(v, p, e, vp, pp, NULL);
    return;
}


bool is_prime(mpz_t n, uint64_t iters) {
    mpz_t n_clone;
    mpz_t n_1; // var to hold n - 1
    mpz_t nminusone; 
    mpz_t s;
    mpz_t r;
    mpz_t sminus; // var to hold s - 1 
    mpz_inits(n_clone, n_1, nminusone, r, s, sminus, NULL);
    mpz_t a;
    mpz_t y;
    mpz_t j;
    mpz_t upperrange;
    mpz_t two; // var to hold the number 2 
    mpz_inits(a, y, j, upperrange, two, NULL);

    mpz_set_ui(two, 2);
    mpz_set(n_clone, n); // n_clone = n 
    mpz_sub_ui(n_1, n, 1); // n_1 = n - 1, changes throughout the code
    mpz_sub_ui(nminusone, n, 1); // nminus = n - 1; does not change
    
    if (mpz_cmp_ui(n, 0) == 0) {
	mpz_clears(n_clone, n_1, nminusone, r, s, sminus, NULL);
        mpz_clears(a, y, j, upperrange, two, NULL);
        return false;
    }

    if (mpz_cmp_ui(n, 1) == 0) {
        mpz_clears(n_clone, n_1, nminusone, r, s, sminus, NULL);
	mpz_clears(a, y, j, upperrange, two, NULL);
        return false;
    }

    if (mpz_cmp_ui(n, 2) == 0) {
        mpz_clears(n_clone, n_1, nminusone, r, s, sminus, NULL);
	mpz_clears(a, y, j, upperrange, two, NULL);
        return true;
    }

    if (mpz_cmp_ui(n, 3) == 0) {
        mpz_clears(n_clone, n_1, nminusone, r, s, sminus, NULL);
	mpz_clears(a, y, j, upperrange, two, NULL);
        return true;
    }

    if (mpz_odd_p(n) != 0) {
        for (mpz_set_ui(s, 0); mpz_even_p(n_1) != 0; mpz_add_ui(s, s, 1)) {
	    mpz_fdiv_q_ui(n_1, n_clone, 2); 
            mpz_set(n_clone, n_1);
        }
	mpz_set(r, n_clone);
	mpz_sub_ui(upperrange, n, 3);
        for (uint64_t i = 1; i <= iters; i++) {
            mpz_urandomm(a, state, upperrange); // choose random a from range {2,..., n - 2)
            mpz_add_ui(a, a, 2); // a = a + 2, to start the range at 2
	    pow_mod(y, a, r, n); // y = power mod(a, r, n)
            if ((mpz_cmp_ui(y, 1) != 0) && (mpz_cmp(y, nminusone) != 0)) {  
	        mpz_set_ui(j, 1);
		mpz_sub_ui(sminus, s, 1); // TWISHA 
	        while ((mpz_cmp(j, sminus) != 1) && (mpz_cmp(y, nminusone) != 0)) { // while j <= s-1 & y != n - 1
		    pow_mod(y, y, two, n);
		    if ((mpz_cmp_ui(y, 1) == 0)) {
		        mpz_clears(n_clone, n_1, nminusone, r, s, sminus, NULL);
		        mpz_clears(a, y, j, upperrange, two, NULL);
		        return false;
		    }
		    mpz_add_ui(j, j, 1);
	        }
	        if (mpz_cmp(y, nminusone) != 0) { 
                    mpz_clears(n_clone, n_1, nminusone, r, s, sminus, NULL);
		    mpz_clears(a, y, j, upperrange, two, NULL);
		    return false;
	        }	
	    }
        }
        mpz_clears(n_clone, n_1, nminusone, r, s, sminus, NULL);
        mpz_clears(a, y, j, upperrange, two, NULL);
        return true;
    }

    mpz_clears(n_clone, n_1, nminusone, r, s, sminus, NULL);
    mpz_clears(a, y, j, upperrange, two, NULL);
    return false;
}


void make_prime(mpz_t p, uint64_t bits, uint64_t iters) {
    mpz_t var; 
    mpz_t two; 
    mpz_t var1;
    mpz_t var2;
    mpz_inits(var, two, var1, var2, NULL);
    mpz_set_ui(two, 2);
    mpz_pow_ui(var, two, bits); // v = 2^bits
    mpz_set_ui(var1, 0);
    mpz_set_ui(var2, 0);
    
    while(is_prime(var1, iters) == false) {
	mpz_rrandomb(var2, state, bits);
        mpz_add(var1, var2, var); // CREDIT: Eugene Section 02_04_2022
    }

    mpz_set(p, var1);
    mpz_clears(var, two, var1, var2, NULL);
    return;
}


void gcd( mpz_t d, mpz_t a, mpz_t b) {
    mpz_t temp;
    mpz_t a_clone;
    mpz_t b_clone;
    mpz_inits(temp, a_clone, b_clone, NULL);   
    mpz_set(a_clone, a);
    mpz_set(b_clone, b); 
    
    while(mpz_cmp_ui(b_clone, 0) == 1 || mpz_cmp_ui(b_clone, 0) == -1) { // while the compare function does not return 0
        mpz_set(temp, b_clone);
        mpz_mod(b_clone, a_clone, b_clone); // b = a mod b 
        mpz_set(a_clone, temp);
    }

    mpz_set(d, a_clone);
    mpz_clears(temp, a_clone, b_clone, NULL);  
    return;    
}


void mod_inverse(mpz_t i, mpz_t a, mpz_t n) {
    // computes the inverse i of modulo n 
    mpz_t r;
    mpz_t r_prime;
    mpz_t t;
    mpz_t t_prime;
    mpz_t q;
    mpz_t r_clone;
    mpz_t t_clone;
    mpz_t t_n;
    mpz_inits(r, r_prime, t, t_prime, q, r_clone, t_clone, t_n, NULL);
    mpz_set(r, n);
    mpz_set(r_prime, a);
    mpz_set_ui(t, 0);
    mpz_set_ui(t_prime, 1);
    
    while(mpz_cmp_ui(r_prime, 0) != 0) {
        mpz_fdiv_q(q, r, r_prime);
        mpz_set(r_clone, r); // start parallel assingment r_clone = r
        mpz_set(r, r_prime); // r = r_prime
        mpz_submul(r_clone, q, r_prime); // r_clone = r_clone (r) - q x r_prime
        mpz_set(r_prime, r_clone); // r_prime = r_clone
        mpz_set(t_clone, t); // t_clone = t
        mpz_set(t, t_prime); // t = t_prime
        mpz_submul(t_clone, q, t_prime); // t_clone = t_clone (t) - q x t_prime
        mpz_set(t_prime, t_clone); // end parallel assingment t_prime = t_clone
    }
    
    if(mpz_cmp_ui(r, 1) == 1) {
        mpz_set_ui(i, 0);
        mpz_clears(r, r_prime, t, t_prime, q, r_clone, t_clone, t_n, NULL);
        return;
    }

    if(mpz_cmp_ui(t, 0) == -1) {
        mpz_add(t_n, t, n);
        mpz_set(t, t_n);
    }

    mpz_set(i, t);
    mpz_clears(r, r_prime, t, t_prime, q, r_clone, t_clone, t_n, NULL);
    return;
}

