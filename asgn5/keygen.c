#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <gmp.h>
#include <time.h>
#include <sys/stat.h>
#include "numtheory.h"
#include "randstate.h"
#include "rsa.h"

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

int main(int argc, char **argv) {
    int opt = 0;
    bool key_b = false;
    bool key_i = false;
    bool key_n = false;
    bool key_d = false;
    bool key_s = false;
    bool key_v = false;
    bool key_h = false;
    
    uint64_t nbits = 256;
    uint64_t iters = 50;
    char *public = "rsa.pub"; // (defualt: rsa.pub)
    char *private = "rsa.priv"; // (defualt: rsa.priv) 
    uint64_t seed = time(NULL);
    
    // begin get opt loop 
    while ((opt = getopt(argc, argv, "b:i:n:d:s:vh")) != -1) {
        switch (opt) {
	// specifies the minimum bits needed for the public modulus n 
	case 'b':
	    key_b = true;
            nbits = strtod(optarg, NULL);     
	    break;
	
	// specifies the number of Miller-Rabin iterations for testing primes 
	case 'i':
	    key_i = true;
	    iters = strtod(optarg, NULL);
	    break;

	// specifies the public key file (defualt: rsa.pub)
	case 'n':
	    key_n = true;
	    public = optarg;
	    break;
	
	// specifies the private key file (defualt: rsa.priv)
	case 'd':
	    key_d = true;
	    private = optarg;
	    break;

	// specifies the random seed for the random state initialization 
	// (defualt: the seconds since UINX epoch, given by time(NULL)
	case 's':
	    key_s = true;
	    seed = strtod(optarg, NULL);
	    break;

	// enables verbose output
	case 'v':
	    key_v = true;
	    break;

	// displays program synopsis and usage 
	case 'h':
	    key_h = true;
	    printf("display program synopsis");
	    break;
	}
    } 

    FILE *pb_file = fopen(public, "w"); // open the public key files using fopen
    FILE *pv_file = fopen(private, "w"); // open the private keys files using fopen 

    // print a helpful error and exit the program in the event of failure 
    if (pb_file == NULL) {
        printf("ERROR: pbfile could not be opened");
    }
    if (pv_file == NULL) {
        printf("ERROR: pvfile could not be opened");
    }

    // using fchmod() and fileno(), make sure the private key file permissions are set to 0600, indicating read and write permissions for the user, and no permissions for anyone else     
    fchmod(fileno(pv_file), 0660); // CREDIT: Eugene office hours 02_16_2022

    // inatilize the random state using randstate_init(), using the set seed 
    mpz_t n;
    mpz_t d;
    mpz_t s;
    mpz_t m;
    mpz_t p;
    mpz_t q;
    mpz_t e;
    mpz_inits(n, d, s, m, p, q, e, NULL);
    randstate_init(seed);

    // make the public and private keys using rsa_make_pub() and rsa_make_priv(), respectively 
    rsa_make_pub(p, q, n, e, nbits, iters);
    rsa_make_priv(d, e, p, q);

    // get the current user's name as a string, use getenv()
    char *username = getenv("USER");

    // convert the username into an mpz_t with mpz_set_str(), specifying the base as 62, then use rsa_sign() to compute the signature of the username 
    mpz_set_str(m, username, 62);
    rsa_sign(s, m, d, n);
		    
    // write the computed public and private key into their respective files 
    rsa_write_pub(n, e, s, username, pb_file);
    rsa_write_priv(n, d, pv_file);

    // if verbose output is enabled, print the following, each with a trailing newline, in order:
    if (key_v) {
        gmp_printf("user = %s\n", username);
        size_t b_size = mpz_sizeinbase(s, 2);
        gmp_printf("s (%zu bits) =  %Zd\n", b_size, s);
        size_t p_size = mpz_sizeinbase(p, 2);
        gmp_printf("p (%zu bits) =  %Zd\n", p_size, p);
        size_t q_size = mpz_sizeinbase(q, 2);
        gmp_printf("q (%zu bits) =  %Zd\n", q_size, q);
        size_t n_size = mpz_sizeinbase(n, 2);
        gmp_printf("n (%zu bits) =  %Zd\n", n_size, n);
        size_t e_size = mpz_sizeinbase(e, 2);
        gmp_printf("e (%zu bits) =  %Zd\n", e_size, e);
        size_t d_size = mpz_sizeinbase(d, 2);
        gmp_printf("d (%zu bits) =  %Zd\n", d_size, d);
    }

    // close the public and private key files, clear the random state with randstate_clear(), and clear and mpz_t variables you may have used 
    fclose(pv_file);
    fclose(pb_file);
    randstate_clear();
    mpz_clears(n, d, s, m, p, q, e, NULL);
    return 0;
}
