#include "mathlib.h"
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h> 

// usage: ./main [-h] [-g] [-n count]
// -a: prints the numerical integration of the square root of one minus x to the forth 
// 

//void i_a; 
//void i_b; 
//void i_c;
//void i_d;
//void i_f;
//void i_g;
//void i_h;
//void i_i;
//void i_j;

int main(int argc, char **argv) { // use getopt() loop to parse arguments
    int opt = 0;
    bool i_a = false;
    bool i_b = false;
    bool i_c = false;
    bool i_d = false;
    bool i_e = false;
    bool i_f = false;
    bool i_g = false;
    bool i_h = false;
    bool i_i = false;
    bool i_j = false;
    bool i_n = false;
    bool i_p = false;
    bool i_q = false;
    int low = 0;
    int high = 10000;
    int partition = 100;
    while ((opt = getopt(argc, argv, "a:b:c:d:e:f:g:h:i:j:n:p:q:H")) != -1) {
        switch (opt) {
	case 'a':
            i_a = true;
	    break;
	case 'b':
	    i_b = true;
            break;
	case 'c':
            i_c = true;
	    break; 
	case 'd':
	    i_d = true;
	    break;
	case 'e':
	    i_e = true;
	    break; 
	case 'f':
	    i_f = true;
	    break;
	case 'g':
	    i_g = true;
	    break;
	case 'h':
	    i_h = true;
	    break;
	case 'i':
	    i_i = true;
	    break;
	case 'j': 
	    i_j = true;
	    break;
	case 'n': // partitions
	    i_n = true; 
	    partition = atoi(optarg);
	    break;
	case 'p': // low
	    i_p = true; 
            low = atoi(optarg); 
	    break;
	case 'q': // high
	    i_q = true; 
	    high = atoi(optarg); 
	    break; 
	case 'H': // program usage and synopsis
	    break;
	default:
	    fprintf(stderr, "error\n");
	    return 1;
	}
    }
    if (i_a) {
	integrate(a, low, high, partition);
	printf("sqrt(1 - x^4)");
    }  	

    if (i_b) {
        printf("1/log(x)");
        integrate(b, low, high, partition);
    } 

    if (i_c) {
        printf("e^(-x^2)");
        integrate(c, low, high, partition);
    }

    if (i_d) {
        printf("sin(x^2)");
        integrate(d, low, high, partition);
    }

    if (i_e) {
        printf("cos(x^2)");
        integrate(e, low, high, partition);
    }

    if (i_f) {
        printf("log(log(x))");
        integrate(f, low, high, partition);
    }

    if (i_g) {
        printf("sin(x)/x");
        integrate(g, low, high, partition);
    }

    if (i_h) {
        printf("e^(-x)/x");
        integrate(h, low, high, partition);
    }

    if (i_i) {
        printf("e^e^x");
        integrate(i, low, high, partition);
    }

    if (i_j) {
        printf("sqrt(sin^2(x) + cos^2(x)");
        integrate(j, low, high, partition);
    }
    return 0;  
}
