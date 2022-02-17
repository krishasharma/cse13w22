#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
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
// Eugene is once again cited in keygen.c for explaining how to properly implement fchmod() and fileno() 
// in keygen.c during his office hours on 02_16_2022
// Omar is cited in numtheory.c for explaining how to implement the mpz functions from the GMP library
// Brian is cited in rsa.c specifically in rsa_make_pub for explaining how to generate a random number
// in the range specified in the asgn_5 PDF

int main(int argc, char **argv) {
    int opt = 0;
    bool en_i = false;
    bool en_o = false;
    bool en_n = false;
    bool en_v = false;
    bool en_h = false;
    
    FILE *infile = stdin;
    FILE *outfile = stdout;

    char *public = "rsa.pub"; // (defualt: rsa.pub)
    
    while ((opt = getopt(argc, argv, "i:o:n:vh")) != -1) {
        switch (opt) {
        // specifies the input file to encrypt (default: stdin)
        case 'i':
            en_i = true;
            infile = fopen(optarg, "r");
	    break;

        // specifies the output file to encrypt (default: stdout) 
        case 'o':
            en_o = true;
	    outfile = fopen(optarg, "w");
            break;

        // specifies the file containing the public key (defualt: rsa.pub)
        case 'n':
            en_n = true;
            public = optarg;
            break;

        // enables verbose output
        case 'v':
            en_v = true;
            break;

        // displays the program synopsis and usage
        case 'h':
            en_h = true;
            break;
        }
    }
    
    FILE *pb_file = fopen(public, "r"); // open public key files
    
    mpz_t n;
    mpz_t d;
    mpz_t s;
    mpz_t m;
    mpz_t p;
    mpz_t q;
    mpz_t e;
    mpz_inits(n, d, s, m, p, q, e, NULL);

    if (pb_file == NULL) {
        printf("ERROR: the file could not be opened");
	mpz_clears(n, d, s, m, p, q, e, NULL);
	fclose(pb_file);
	exit(EXIT_FAILURE);
    }

    char *username = getenv("USER"); // get the current user's name -> use getenv()???
    rsa_read_pub(n, e, s, username, pb_file);    

    if (en_v) {
        gmp_printf("user = %s\n", username);
        size_t b_size = mpz_sizeinbase(s, 2);
        gmp_printf("s (%zu bits) =  %Zd\n", b_size, s);
        size_t n_size = mpz_sizeinbase(n, 2);
        gmp_printf("n (%zu bits) =  %Zd\n", n_size, n);
        size_t e_size = mpz_sizeinbase(e, 2);
        gmp_printf("e (%zu bits) =  %Zd\n", e_size, e);
    } 

    if (en_h) {
	printf("USAGE: ./encrypt\n");
        printf("// -i : specifies the input file to encrypt (default: stdin)\n");
        printf("// -o : specifies the output file to encrypt (default: stdout)\n");
        printf("// -n : specifies the file containing the public key\n");
        printf("// -v : enables verbose output\n");
        printf("// -h : displays the program's usage and synopsis\n");
    }

    mpz_set_str(m, username, 62);
    if (rsa_verify(m, s, e, n) == false) { 
        printf("ERROR: the signature could not be verified");
	mpz_clears(n, d, s, m, p, q, e, NULL);
	fclose(pb_file);
	exit(EXIT_FAILURE);
    }

    rsa_encrypt_file(infile, outfile, n, e);
    
    fclose(infile);
    fclose(outfile);
    fclose(pb_file);
    mpz_clears(n, d, s, m, p, q, e, NULL);
}
