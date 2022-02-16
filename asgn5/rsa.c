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
	
    uint64_t pbits = (rand() % (nbits / 2) + nbits / 4); // generate pbits random bit number
    uint64_t qbits = nbits - pbits; // remain bits are qbits
    
    make_prime(p, pbits, iters); // create a prime number p
    make_prime(q, qbits, iters); // create a prime number q
    
    mpz_mul(n, p, q); // n = p x q

    mpz_t p_1;
    mpz_t q_1; 
    mpz_t gcd_out;
    mpz_t p1_q1;
    mpz_t lcm_out;
    mpz_t gcd_e;
    mpz_inits(p_1, q_1, gcd_out, p1_q1, lcm_out, gcd_e, NULL);
    
    mpz_sub_ui(p_1, p, 1); // p_1 = p - 1
    mpz_sub_ui(q_1, q, 1); // q_1 = q - 1
    
    gcd(gcd_out, p_1, q_1); // gcd of p_1 and q_1 stored in gcd_out
    mpz_mul(p1_q1, p_1, q_1); // p_1 x q_1 stored in p1_q1
    mpz_fdiv_q(lcm_out, p1_q1, gcd_out); // lcm_out(lambda n) = (p_1 x q_1) / gcd(p_1, q_1)
    mpz_set_ui(gcd_e, 0);
    
    while(mpz_cmp_ui(gcd_e, 1) != 0) { // while e isnt coprime (gcd of e and lambda n doesnt equal 1)
        mpz_urandomb(e, state, nbits); // generate random number of nbits
        gcd(gcd_e, e, lcm_out); // find gcd of the random number and lambda n
    }
    
    // the value e holds should be a coprime of lambda n -> its now the public exponent
    mpz_clears(p_1, q_1, gcd_out, p1_q1, lcm_out, gcd_e, NULL);
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
    gmp_fprintf(pbfile, "%s\n", username);
}


void rsa_read_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {
    // reads a public RSA key from pbfile
    gmp_fscanf(pbfile, "%Zx\n", n);
    gmp_fscanf(pbfile, "%Zx\n", e);
    gmp_fscanf(pbfile, "%Zx\n", s);
    gmp_fscanf(pbfile, "%s\n", username);
}


void rsa_make_priv(mpz_t d, mpz_t e, mpz_t p, mpz_t q) {
    // creates a new RSA private key d given primes p and q and public exponenet e 
    // e modulo lambda(n) = lcm(p - 1, q - 1)
    mpz_t p_1;
    mpz_t q_1;
    mpz_t gcd_out;
    mpz_t p1_q1;
    mpz_t lcm_out;
    mpz_inits(p_1, q_1, gcd_out, p1_q1, lcm_out, NULL);
    
    mpz_sub_ui(p_1, p, 1); // p_1 = p - 1
    mpz_sub_ui(q_1, q, 1); // q_1 = q - 1
    
    gcd(gcd_out, p_1, q_1); // gcd of p_1 and q_1 stored in gcd_out
    mpz_mul(p1_q1, p_1, q_1); // p_1 x q_1 stored in p1_q1
    mpz_fdiv_q(lcm_out, p1_q1, gcd_out); // lcm_out(lambda n) = (p_1 x q_1) / gcd(p_1, q_1)
    mod_inverse(d, e, lcm_out);
    
    mpz_clears(p_1, q_1, gcd_out, p1_q1, lcm_out, NULL);
    return;
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
    gmp_fscanf(pvfile, "%ZX\n", d);
}

void rsa_encrypt(mpz_t c, mpz_t m, mpz_t e, mpz_t n) {
    // preforms RSA encryption 
    // E(m) = c = m^e (mod n) 
    pow_mod(c, m, e, n);
    return;
}

void rsa_encrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t e) {
    // encrypts the contents of infile, writing the encrypted contents to outfile
    mpz_t m;
    mpz_t encrypt;
    
    printf("test 1\n");
    
    mpz_inits(m, encrypt, NULL);
    
    size_t j = 0;
    
    printf("test 2\n");
    
    size_t log_n = mpz_sizeinbase(n, 2); // log_n = log2n
    log_n = log_n - 1; //mpz_sub_ui(log_n, log_n, 1); 
    size_t k = log_n / 8; //mpz_fdiv_q_ui(k, log_n, 8); 
    
    printf("test 3\n");
    
    uint8_t *block = (uint8_t *)calloc(k, sizeof(uint8_t)); // allocate an array that can hold k bytes
    block[0] = 0xFF; // set the 0th byte of the block to 0xFF
    
    printf("test 4\n");
    
    while(!feof(infile)) {
        printf("test 5\n");
        
	j = fread(&block[1], sizeof(uint8_t), k - 1, infile); // read the file f read
        
	printf("test 6\n");
        
	mpz_import(m, j, 1, sizeof(uint8_t), 1, 0, block); // mpz import turn the bytes into number
        
	printf("test 7\n");
        
	rsa_encrypt(encrypt, m, e, n); // encrypt use rsa encrypt 
        
	printf("test 8\n");
        
	gmp_fprintf(outfile, "%Zx\n",  encrypt); // gmp fprintf write block (number) to output
        
	printf("test 9\n");
    }
    printf("test 10\n");
    
    mpz_clears(m, encrypt, NULL);
    free(block);
    
    printf("test 11\n");
}

void rsa_decrypt(mpz_t m, mpz_t c, mpz_t d, mpz_t n) {
    // preforms RSA decryption 
    // D(c) = m = c^d (mod n)
    pow_mod(m, c, d, n);
    return;
}

void rsa_decrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t d) {
    // decrypts the contents of infile, writing the decrypted contents to outfile
    printf("test a\n");
    
    mpz_t c;
    mpz_t decrypt;
    mpz_inits(c, decrypt, NULL);
    
    printf("test b\n");
    
    size_t j;
    size_t log_n = mpz_sizeinbase(n, 2); // log_n = log2n
    log_n = log_n - 1;
    
    printf("test c\n");
    
    size_t k = log_n / 8;
    uint8_t *block = (uint8_t *)calloc(k, sizeof(uint8_t)); // allocate an array that can hold k bytes
    block[0] = 0xFF; // set the 0th byte of the block to 0xFF
    
    printf("test d\n");
    
    while(!feof(infile)) {
        //printf("test e\n");
        
	gmp_fscanf(outfile, "%Zx\n", c); // gmp_fscanf
        
	//printf("test f\n");
        
	gmp_printf("c : %Zx\n", c);
        rsa_decrypt(decrypt, c, d, n); // decrypt using rsa decrypt
        
	//printf("test g\n");
        
	mpz_export(block, &j, 1, sizeof(uint8_t), 1, 0, c); // mpz_export to turn the
        
	//printf("test h\n");
        
	fwrite(&block[1], sizeof(uint8_t), j - 1, outfile); // write the file fwrite?? IDK ABOUT THIS ONE
        
	//printf("test i\n");
    } 
    printf("test j\n");
    
    mpz_clears(c, decrypt,  NULL);
    free(block);
    
    printf("test k\n");
}

void rsa_sign(mpz_t s, mpz_t m, mpz_t d, mpz_t n) {
    // prefroms RSA sigining 
    // S(m) = s = m^d (mod n)
    pow_mod(s, m, d, n);
    return;
}

bool rsa_verify(mpz_t m, mpz_t s, mpz_t e, mpz_t n) {
    // preforms RSA verification, returns true if signature s is verified and false otherwise
    // verification is the inverse of signing 
    // t = V(s) = s^e (mod n)
    mpz_t t;
    mpz_init(t);
    pow_mod(t, s, e, n);
    if(mpz_cmp(t, m) == 0) {
        return true;
    }
    else {
        return false;
    }
    mpz_clears(t, NULL);
}
