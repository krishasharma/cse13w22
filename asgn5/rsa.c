#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>
#include <time.h>
#include "numtheory.h"
#include "randstate.h"
#include "rsa.h"

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


void rsa_make_pub(mpz_t p, mpz_t q, mpz_t n, mpz_t e, uint64_t nbits, uint64_t iters) {
    // creates parts of a new RSA public key
    // two large primes p and q, their product n, and the public exponent e
    mpz_t p_minusone; // var for (p - 1) 
    mpz_t q_minusone; // var for (q - 1)
    mpz_t pq_mul; // var for (p - 1) * (q - 1), primes are always 0 or pos, so abs is not needed
    mpz_t gcd_pq; // var for gcd((p - 1) * (q - 1))
    mpz_t lcm_pq; // var for lcm of |(p - 1) * (q - 1)| / gcd((p - 1) * (q - 1)) aka lambda(n)
    mpz_t gcd_e; // var to check if e is a coprime with lambda(n) or (lcm_pq) 
    mpz_inits(p_minusone, q_minusone, pq_mul, gcd_pq, lcm_pq, gcd_e, NULL);
    
    uint64_t pbits = (rand() % (nbits / 2) + nbits / 4); // begin generating the bits 
    uint64_t qbits = nbits - pbits; // calculate the remainder of the bits

    make_prime(p, pbits, iters); // generates a large prime number of pbits length  
    make_prime(q, qbits, iters); // generates a large prime number of the remainder of the bits 
     
    mpz_mul(n, p, q); // n = pq
    
    mpz_sub_ui(p_minusone, p, 1); // p - 1 
    mpz_sub_ui(q_minusone, q, 1); // q - 1 
    gcd(gcd_pq, p_minusone, q_minusone); // gcd of (p - 1) and (q - 1)
    mpz_mul(pq_mul, p_minusone, q_minusone); // (p - 1) * (q - 1)
    mpz_fdiv_q(lcm_pq, pq_mul, gcd_pq); // abs((p - 1) * (q - 1)/ gcd((p - 1) * (q - 1)
    
    mpz_set_ui(gcd_e, 0); // set gcd_e = 0

    while (mpz_cmp_ui(gcd_e, 1) != 0) { // while e is not coprime, if e == 1: quit
        mpz_urandomb(e, state, nbits); // generate random numbers of nbits 
	gcd(gcd_e, e, lcm_pq); // compute the gcd of each random num and lambda(n)
    }
    
    printf("nibits = %lu\n", nbits); 
    printf("pbits = %lu\n", pbits);
    printf("qbits = %lu\n", qbits);

    mpz_clears(p_minusone, q_minusone, pq_mul, gcd_pq, lcm_pq, gcd_e, NULL);
    return;
}


void rsa_write_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {
    // writes a public RSA key to pbfile
    // format should be n, e, s, username (all with trailing newline)
    // values of n, e, s should be written as hexstrings 
    // take the values given and write it out to the outfile
    gmp_fprintf(pbfile, "%Zx\n", n);
    gmp_fprintf(pbfile, "%Zx\n", e);
    gmp_fprintf(pbfile, "%Zx\n", s);
    fprintf(pbfile, "%s\n", username); // ASK ABOUT THIS TMRW IN SECTION
}



void rsa_read_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {
    // reads a public RSA key from pbfile
    gmp_fscanf(pbfile, "%Zx\n", n);
    gmp_fscanf(pbfile, "%Zx\n", e);
    gmp_fscanf(pbfile, "%Zx\n", s);
    fscanf(pbfile, "%s\n", username);
}


void rsa_make_priv(mpz_t d, mpz_t e, mpz_t p, mpz_t q) {
    // creates a new RSA private key d given primes p and q and public exponenet e 
    // e modulo lambda(n) = lcm(p - 1, q - 1)
    mpz_t p_minusone; // var for (p - 1) 
    mpz_t q_minusone; // var for (q - 1)
    mpz_t pq_mul; // var for (p - 1) * (q - 1), primes are always 0 or pos, so abs is not needed
    mpz_t gcd_pq; // var for gcd((p - 1) * (q - 1))
    mpz_t lcm_pq; // var for lcm of |(p - 1) * (q - 1)| / gcd((p - 1) * (q - 1)) aka lambda(n)
    mpz_inits(p_minusone, q_minusone, pq_mul, gcd_pq, lcm_pq, NULL); 

    mpz_sub_ui(p_minusone, p, 1); // p - 1 
    mpz_sub_ui(q_minusone, q, 1); // q - 1 
    gcd(gcd_pq, p_minusone, q_minusone); // gcd of (p - 1) and (q - 1)
    mpz_mul(pq_mul, p_minusone, q_minusone); // (p - 1) * (q - 1)
    mpz_fdiv_q(lcm_pq, pq_mul, gcd_pq); // abs((p - 1) * (q - 1)/ gcd((p - 1) * (q - 1)

    mod_inverse(d, e, lcm_pq);
    gmp_printf("d: %Zd", d);
} 


void rsa_write_priv(mpz_t n, mpz_t d, FILE *pvfile) {
    // writes a private key to pvfile
    // the format should be n then d, both with a trailing new line 
    // both values should be hexstrings 
    gmp_fprintf(pvfile, "%Zx\n", n);
    gmp_fprintf(pvfile, "%Zx\n", d);
}


void rsa_read_priv(mpz_t n, mpz_t d, FILE *pvfile) {
    // reads a private key from pvfile 
    gmp_fscanf(pvfile, "%Zx\n", n);
    gmp_fscanf(pvfile, "%Zx\n", d);
}


void rsa_encrypt(mpz_t c, mpz_t m, mpz_t e, mpz_t n) {
    // preforms RSA encryption 
    // E(m) = c = m^e (mod n) 
    pow_mod(c, m, e, n);
}


void rsa_encrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t e) {
    // encrypts the contents of infile, writing the encrypted contents to outfile
    mpz_t k;
    mpz_inits(k, NULL);
    size_t log_n = mpz_sizeinbase(n, 2);
    
    mpz_sub_ui(log_n, log_n, 1);
    mpz_fdiv_q_ui(k, log_n, 8);
    block = (uint64_t *)calloc(k, sizeof(uint64_t)); 
    block[0] = 1111;

    mpz_clears(k, NULL); 

    while (feof(infile)) {
    
    }
} 


void rsa_decrypt(mpz_t m, mpz_t c, mpz_t d, mpz_t n) {
    // preforms RSA decryption 
    // D(c) = m = c^d (mod n) 
    pow_mod(m, c, d, n);
}


/*void rsa_decrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t d) {
    // decrypts the contents of infile, writing the decrypted contents to outfile
} */


void rsa_sign(mpz_t s, mpz_t m, mpz_t d, mpz_t n) {
    // prefroms RSA sigining 
    // S(m) = s = m^d (mod n)
    pow_mod(s, m, d, n);
}


bool rsa_verify(mpz_t m, mpz_t s, mpz_t e, mpz_t n) {
    // preforms RSA verification, returns true if signature s is verified and false otherwise
    // verification is the inverse of signing 
    // t = V(s) = s^e (mod n)
    mpz_t t;
    mpz_init(t);
    
    pow_mod(t, s, e, n);
    gmp_printf("t: %Zd\n", t);
    
    if(mpz_cmp(t, m) == 0) {
        return true;
    }
    else {
        return false;
    }

    mpz_clears(t, NULL);
}
