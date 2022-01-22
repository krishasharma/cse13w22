#include "mathlib.h"
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h> 

// usage: ./integrate [-h] [-g] [-n count]
// -a: prints the numerical integration of sqrt(1-x^4) 
// -b: prints the numerical integration of 1/log(x)
// -c: prints the numerical integration of e^(-x^2)
// -d: prints the numerical integration of sin(x^2)
// -e: prints the numerical integration of cos(x^2)
// -f: prints the numerical integration of log(log(x)
// -g: prints the numerical integration of sin(x)/x
// -h: prints the numerical integration of e^(-x)/x
// -i: prints the numerical integration of e^e^x
// -j: prints the numerical integration of sqrt(sin^2(x) + cos^2(x)
// -n: sets the upper limit of partitions. 
// -p: sets the low end of the interval to integrate over to low.
// -q: sets the high end of the interval to integrate over to high.
// -H: displays the program's usage and synopsis.

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
    //bool p = false;
    //bool q = false;
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
	    //p = true;
            low = strtod(optarg, NULL); 
	    break;
	case 'q': // high
	    //q = true;
	    high = strtod(optarg, NULL); 
	    break; 
	case 'H': // program usage and synopsis
	    printf(" -a: prints the numerical integration of sqrt(1-x^4)\n");
	    printf(" -b: prints the numerical integration of 1/log(x)\n");
	    printf(" -c: prints the numerical integration of e^(-x^2)\n");
	    printf(" -d: prints the numerical integration of sin(x^2)\n");
	    printf(" -e: prints the numerical integration of cos(x^2)\n");
	    printf(" -f: prints the numerical integration of log(log(x)\n");
	    printf(" -g: prints the numerical integration of sin(x)/x\n");
	    printf(" -h: prints the numerical integration of e^(-x)/x\n");
	    printf(" -i: prints the numerical integration of e^e^x\n");
	    printf(" -j: prints the numerical integration of sqrt(sin^2(x) + cos^2(x)\n");
	    printf(" -n: sets the upper limit of partitions.\n");
	    printf(" -p: sets the low end of the interval to integrate over to low.\n");
	    printf(" -q: sets the high end of the interval to integrate over to high.\n");
	    printf(" -H: displays the program's usage and synopsis.\n");
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
    }
    return 0;  
}
