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
// There is also high level pseudocode collaboration with my sister Twisha Sharma (tvsharma)
// Audrey is cited in randstate.c as she provided pseudocode for it during her tutoring section 
// on 02_09_2022
// Eugene is cited in numtheory.c for the pseudocode for the pow_mod and the is_prime functions 
// given during his lab section on 02_04_2022
// Eugene is also cited in numtheory.c make_prime specifically for for the idea of 
// adding 2^bits + the random num generated from urandomb that caps at user input bits given
// Omar is cited in numtheory.c for explaining how to implement the mpz functions from the GMP library
// Brian is cited in rsa.c specifically in rsa_make_pub for explaining how to generate a random number
// in the range specified in the asgn_5 PDF 

int main(int argc, char **argv) {
    bool k_b = false;
    bool k_i = false;
    bool k_n = false;
    bool k_d = false;
    bool k_s = false;
    bool k_v = false;
    bool k_h = false;
    
    // begin get opt loop 
    while ((opt = getopt(argc, argv, "bindsv")) != -1) {
        switch (opt) {
	case 'b':
	    k_b = true;
	    break;
	
	case 'i':
	    k_i = true;
	    break;

	case 'n':
	    k_n = true;
	    break;
	
	case 'd':
	    k_d = true;
	    break;

	case 's':
	    k_s = true;
	    break;

	case 'v':
	    k_v = true;
	    break;

	case 'h':
	    k_h = true;
	    break;
	}

    }

    FILE *pb = fopen("pbfile", "r"); // open the public key files using fopen
    FILE *pv = fopen("pvfile", "r"); // open the private keys files using fopen 

    // print a helpful error and exit the program in the event of failure 
    
    // using fchmod() and fileno(), make sure the private key file permissions are set to 0600, indicating read and write permissions for the user, and no permissions for anyone else 

    // inatilize the random state using randstate_init(), using the set seed 

    // make the public and private keys using rsa_make_pub() and rsa_make_priv(), respectively 

    // get the current user's name as a string, use getenv()

    // convert the username into an mpz_t with mpz_set_str(), specifying the base as 62, then use rsa_sign() to compute the signature of the username 

    // write the computed public and private key into their respective files 

    // if verbose output is enabled, print the following, each with a trailing newline, in order:

        // gmp_printf("username is %s\n", user);
        // gmp_printf("the signature is: %Zd\n", s);
        // gmp_printf("the first large prime is: %Zd\n", p);
        // gmp_printf("the second large prime is: %Zd\n", q);
        // gmp_printf("the public modulus is: %Zd\n", n);
        // gmp_printf("the public exponent: %Zd\n", e);
        // gmp_printf("the private key: %Zd\n", d); 

    // close the public and private key files, clear the random state with randstate_clear(), and clear and mpz_t variables you may have used 

}
