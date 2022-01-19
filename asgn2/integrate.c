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
    double low  = 0;   
    double high = 10000; 
    int partition = 100;
    while ((opt = getopt(argc, argv, "abcdefghijn:p:q:H")) != -1) {
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
	case 'n': // partition
	    i_n = true; 
	    partition = atoi(optarg);
	    break;
	case 'p': // low
            low = strtod(optarg, NULL); 
	    break;
	case 'q': // high
	    high = strtod(optarg, NULL); 
	    break; 
	case 'H': // program usage and synopsis
	    break;
	default:
	    fprintf(stderr, "error\n");
	    return 1;
	}
    }

    if (i_a) {
	int count = 2;
	printf("sqrt(1 - x^4) ,%f,%f,%d\n", low, high, partition);
	while (partition > count) {  
	    if (partition >= count) {
	        printf("%d,%.15lf\n",count,integrate(a, low, high, count));
                count += 2;
	    }
	    if (partition == count) {
	        printf("%d,%.15lf\n",count,integrate(a, low, high, count));
		break;
	    }
	}
    }  	

    if (i_b) {
        int count = 2;
        printf("1/log(x) ,%f,%f,%d\n", low, high, partition);
        while (partition > count) {
            if (partition >= count) {
                printf("%d,%.15lf\n",count,integrate(b, low, high, count));
                count += 2;
            }
            if (partition == count) {
                printf("%d,%.15lf\n",count,integrate(b, low, high, count));
                break;
            }
        }

        //printf("1/log(x) ,%f,%f,%d\n", low, high, partition);
        //printf("%.15lf\n",integrate(b, low, high, partition));
    } 

    if (i_c) {
        int count = 2;
        printf("e^(-x^2) ,%f,%f,%d\n", low, high, partition);
        while (partition > count) {
            if (partition >= count) {
                printf("%d,%.15lf\n",count,integrate(c, low, high, count));
                count += 2;
            }
            if (partition == count) {
                printf("%d,%.15lf\n",count,integrate(c, low, high, count));
                break;
            }
        }
        //printf("e^(-x^2) ,%f,%f,%d\n", low, high, partition);
        //printf("%.15lf\n",integrate(c, low, high, partition));
    }

    if (i_d) {
	int count = 2;
        printf("sin(x^2) ,%f,%f,%d\n", low, high, partition);
        while (partition > count) {
            if (partition >= count) {
                printf("%d,%.15lf\n",count,integrate(d, low, high, count));
                count += 2;
            }
            if (partition == count) {
                printf("%d,%.15lf\n",count,integrate(d, low, high, count));
                break;
            }
        }
        //printf("sin(x^2) ,%f,%f,%d\n", low, high, partition);
        //printf("%.15lf\n",integrate(d, low, high, partition));
    }

    if (i_e) {
        int count = 2;
        printf("cos(x^2) ,%f,%f,%d\n", low, high, partition);
        while (partition > count) {
            if (partition >= count) {
                printf("%d,%.15lf\n",count,integrate(e, low, high, count));
                count += 2;
            }
            if (partition == count) {
                printf("%d,%.15lf\n",count,integrate(e, low, high, count));
                break;
            }
        }
        //printf("cos(x^2) ,%f,%f,%d\n", low, high, partition);
        //printf("%.15lf\n",integrate(e, low, high, partition));
    }

    if (i_f) {
        int count = 2;
        printf("log(log(x)) ,%f,%f,%d\n", low, high, partition);
        while (partition > count) {
            if (partition >= count) {
                printf("%d,%.15lf\n",count,integrate(f, low, high, count));
                count += 2;
            }
            if (partition == count) {
                printf("%d,%.15lf\n",count,integrate(f, low, high, count));
                break;
            }
        }
        //printf("log(log(x)) ,%f,%f,%d\n", low, high, partition);
        //printf("%.15lf\n",integrate(f, low, high, partition));
    }

    if (i_g) {
	int count = 2;
        printf("sin(x)/x ,%f,%f,%d\n", low, high, partition);
        while (partition > count) {
            if (partition >= count) {
                printf("%d,%.15lf\n",count,integrate(g, low, high, count));
                count += 2;
            }
            if (partition == count) {
                printf("%d,%.15lf\n",count,integrate(g, low, high, count));
                break;
            }
        }
        //printf("sin(x)/x ,%f,%f,%d\n", low, high, partition);
        //printf("%.15lf\n",integrate(g, low, high, partition));
    }

    if (i_h) {
	int count = 2;
        printf("e^(-x)/x ,%f,%f,%d\n", low, high, partition);
        while (partition > count) {
            if (partition >= count) {
                printf("%d,%.15lf\n",count,integrate(h, low, high, count));
                count += 2;
            }
            if (partition == count) {
                printf("%d,%.15lf\n",count,integrate(h, low, high, count));
                break;
            }
        }
        //printf("e^(-x)/x ,%f,%f,%d\n", low, high, partition);
        //printf("%.15lf\n",integrate(h, low, high, partition));
    }

    if (i_i) {
        int count = 2;
        printf("e^e^x ,%f,%f,%d\n", low, high, partition);
        while (partition > count) {
            if (partition >= count) {
                printf("%d,%.15lf\n",count,integrate(i, low, high, count));
                count += 2;
            }
            if (partition == count) {
                printf("%d,%.15lf\n",count,integrate(i, low, high, count));
                break;
            }
        }
        //printf("e^e^x ,%f,%f,%d\n", low, high, partition);
        //printf("%.15lf\n",integrate(i, low, high, partition));
    }

    if (i_j) {
        int count = 2;
        printf("sqrt(sin^2(x) + cos^2(x) ,%f,%f,%d\n", low, high, partition);
        while (partition > count) {
            if (partition >= count) {
                printf("%d,%.15lf\n",count,integrate(j, low, high, count));
                count += 2;
            }
            if (partition == count) {
                printf("%d,%.15lf\n",count,integrate(j, low, high, count));
                break;
            }
        }
        //printf("sqrt(sin^2(x) + cos^2(x) ,%f,%f,%d\n", low, high, partition);
        //printf("%.15lf\n",integrate(j, low, high, partition));
    }
    return 0;  
}
