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
    bool de_i = false;
    bool de_o = false;
    bool de_n = false;
    bool de_v = false;
    bool de_h = false;

    FILE *infile = stdin;
    FILE *outfile = stdout;

    char *private = "rsa.priv"; // (defualt: rsa.priv)

    while ((opt = getopt(argc, argv, "i:o:n:vh")) != -1) {
        switch (opt) {
        // specifies the input file to encrypt (default: stdin)
        case 'i':
            de_i = true;
            infile = fopen(optarg, "r");
            break;

        // specifies the output file to encrypt (default: stdout) 
        case 'o':
            de_o = true;
            outfile = fopen(optarg, "w");
            break;

        // specifies the file containing the private key (defualt: rsa.priv)
        case 'n':
            de_n = true;
            private = optarg;
            break;

        // enables verbose output
        case 'v':
            de_v = true;
            break;

        // displays the program synopsis and usage
        case 'h':
            de_h = true;
            break;
        }
    }

    FILE *pv_file = fopen(private, "r"); // open public key files

    mpz_t n;
    mpz_t d;
    mpz_t s;
    mpz_t m;
    mpz_t p;
    mpz_t q;
    mpz_t e;
    mpz_inits(n, d, s, m, p, q, e, NULL);

    if (pv_file == NULL) {
        printf("ERROR: the file could not be opened");
        mpz_clears(n, d, s, m, p, q, e, NULL);
        fclose(pv_file);
        exit(EXIT_FAILURE);
    }

    char *username = getenv("USER"); // get the current user's name -> use getenv()???
    rsa_read_priv(n, d, pv_file);

    if (de_v) {
        gmp_printf("user = %s\n", username);
        size_t n_size = mpz_sizeinbase(s, 2);
        gmp_printf("n (%zu bits) =  %Zd\n", n_size, n);
        size_t e_size = mpz_sizeinbase(e, 2);
        gmp_printf("e (%zu bits) =  %Zd\n", e_size, e);
        return 0;
    }

    if (de_h) {
        printf("USAGE: ./encrypt\n");
        printf("// -i : specifies the input file to encrypt (default: stdin)\n");
        printf("// -o : specifies the output file to encrypt (default: stdout)\n");
        printf("// -n : specifies the file containing the public key\n");
        printf("// -v : enables verbose output\n");
        printf("// -h : displays the program's usage and synopsis\n");
    }

    rsa_decrypt_file(infile, outfile, n, d);

    fclose(infile);
    fclose(outfile);
    fclose(pv_file);
    mpz_clears(n, d, s, m, p, q, e, NULL);
}

