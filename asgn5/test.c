#include "numtheory.h"
#include "randstate.h"
#include "rsa.h"
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
    
    // RSA_VERIFY TEST 
    mpz_t m;
    mpz_t s;
    mpz_t e;
    mpz_t n;
    mpz_inits(m, s, e, n, NULL);
    
    mpz_set_ui(m, 10);
    mpz_set_ui(s, 20);
    mpz_set_ui(e, 19);
    mpz_set_ui(n, 34);

    rsa_verify(m, s, e, n); 
    
    // RSA_SIGN TEST 
    /*mpz_t s;
    mpz_t m;
    mpz_t d;
    mpz_t n;
    mpz_inits(s, m, d, n, NULL);

    mpz_set_ui(m, 20);
    mpz_set_ui(d, 857425);
    mpz_set_ui(n, 3253421);

    rsa_decrypt(s, m, d, n);
    gmp_printf("s: %Zd\n", s);*/

    // RSA_DECRYPT TEST
    /*mpz_t m;
    mpz_t c;
    mpz_t d;
    mpz_t n;
    mpz_inits(m, c, d, n, NULL);

    mpz_set_ui(c, 20);
    mpz_set_ui(d, 857425);
    mpz_set_ui(n, 3253421);

    rsa_decrypt(m, c, d, n);
    gmp_printf("m: %Zd\n", m);*/


    // RSA_ENCRYPT TEST 
    /*mpz_t m;
    mpz_t c; 
    mpz_t e; 
    mpz_t n;
    mpz_inits(m, c, e, n, NULL);
    
    mpz_set_ui(m, 20);
    mpz_set_ui(e, 857425);
    mpz_set_ui(n, 3253421);
    
    rsa_encrypt(c, m, e, n);
    gmp_printf("c: %Zd\n", c);*/


    // RSA_READ_PRIV TEST 
    /*mpz_t n;
    mpz_t d;
    mpz_inits(n, d, NULL);
    mpz_set_ui(n, 3253421);
    mpz_set_ui(d, 42865);

    FILE *pvfile = NULL;
    pvfile = fopen("pvfile", "w");
    rsa_read_priv(n, d, pvfile);
    fclose(pvfile);*/

    // RSA_WRITE_PRIV TEST
    /*mpz_t n; 
    mpz_t d;
    mpz_inits(n, d, NULL);
    mpz_set_ui(n, 3253421);
    mpz_set_ui(d, 42865);

    FILE *pvfile = NULL;
    pvfile = fopen("pvfile", "w");
    rsa_write_priv(n, d, pvfile);
    fclose(pvfile);*/


    // RSA_MAKE_PRIV TEST 
    /*mpz_t d; 
    mpz_t e;
    mpz_t p;
    mpz_t q;
    mpz_inits(d, e, p, q, NULL);

    mpz_set_ui(e, 857425);
    mpz_set_ui(p, 1613);
    mpz_set_ui(q, 2017);

    rsa_make_priv(d, e, p, q);*/


    // RSA_READ_PUB TEST
    /*mpz_t n;
    mpz_t e;
    mpz_t s;
    mpz_inits(n, e, s, NULL);
    mpz_set_ui(n, 35);
    mpz_set_ui(e, 65537);
    mpz_set_ui(s, 13);

    char krvsharm;
    FILE *pbfile = NULL;

    pbfile = fopen("pbfile", "r");
    rsa_read_pub(n, e, s, &krvsharm, pbfile);
    fclose(pbfile);*/

    // RSA_WRITE_PUB TEST
    /*mpz_t n;
    mpz_t e;
    mpz_t s;
    mpz_inits(n, e, s, NULL);
    mpz_set_ui(n, 35);
    mpz_set_ui(e, 65537);
    mpz_set_ui(s, 13);
    
    char krvsharm;
    FILE *pbfile = NULL;
    
    pbfile = fopen("pbfile", "w");
    rsa_write_pub(n, e, s, &krvsharm, pbfile);
    fclose(pbfile); */

    // RSA_MAKE_PUB TEST
    /*uint64_t nbits = 100; // rsa line 39, test line 60, numtheory 166 
    uint64_t iters = 50;
    mpz_t p;
    mpz_t q;
    mpz_t n;
    mpz_t e;
    mpz_inits(p, q, n, e, NULL);
    rsa_make_pub(p, q, n, e, nbits, iters);

    gmp_printf("p = %Zd\n", p);
    gmp_printf("q = %Zd\n", q);
    gmp_printf("e = %Zd\n", e);  
    gmp_printf("n = %Zd\n", n);*/


    // POW_MOD_TEST 
    /*mpz_t out, base, exponent, modulus;
    mpz_inits(out, base, exponent, modulus, NULL);
    mpz_set_ui(base, 5);
    mpz_set_ui(exponent, 9);
    mpz_set_ui(modulus, 20);
    pow_mod(out, base, exponent, modulus);
    gmp_printf("out is: %Zd\n", out);*/    
    

    // MOD_INVERSE_TEST 
    /*mpz_t i; 
    mpz_t a; 
    mpz_t n; 
    mpz_inits(i, a, n, NULL);

    mpz_set_ui(a, 7);    
    mpz_set_ui(n, 32);
    
    mod_inverse(i, a, n);
    gmp_printf("i is: %Zd\n", i);*/
    

    // MAKE_PRIME_TEST
    /*mpz_t p;
    mpz_init(p);
    uint64_t bits = 20;
    uint64_t iters = 50;
    for (int i = 0; i < 1000; i++) {
        make_prime(p, bits, iters);
        gmp_printf("p is: %Zd\n", p);
    }*/


    // IS_PRIME_TEST 
    /*mpz_t n;
    mpz_inits(n, NULL);
    mpz_srt_ui(n, 17);
    for(int i = 0; i < 100; i++) { 
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


    //mpz_clears(out, base, exponent, modulus, NULL); // clears for pow_mod 
    
    //mpz_clears(i, a, n, NULL); // clears for mod_inverse 
    
    //mpz_clears(p, NULL); // clears for make_prime

    //mpz_clears(n, NULL); // clears for is_prime 
    
    //mpz_clears(p, q, n, e, NULL); // clears for rsa_make_pub
    
    //mpz_clears(n, e, s, NULL); // clears for rsa_write_pub
    
    //mpz_clears(n, e, s, NULL); // clears for rsa_read_pub
    
    //mpz_clears(d, e, p, q, NULL); // clears for rsa_make_priv

    //mpz_clears(n, d, NULL); // clears for rsa_write_priv

    //mpz_clears(n, d, NULL); // clears for rsa_read_priv

    //mpz_clears(m, c, e, n, NULL); // clears for rsa_encrypt

    //mpz_clears(m, c, d, n, NULL); // clears for rsa_decrypt

    //mpz_clears(s, m, d, n, NULL); // clears for rsa_sign 
    
    mpz_clears(m, s, e, n, NULL); // clears for rsa_verify 

    randstate_clear();

}
