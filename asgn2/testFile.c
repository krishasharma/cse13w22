#include "mathlib.h" 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void) {
	//printf("TEST");
	//printf("%f/n", Sin(0));
	printf("Sin Difference:\n");
	for (double i = 10; i < 30; i ++){
		printf("DIFFERENCE = (%.15lf)\n", Sin(i) - sin(i));
	}
	printf("Cos Difference:\n");
	for (double i = 10; i < 30; i ++){
                printf("DIFFERENCE = (%.15lf)\n", Cos(i) - cos(i));
        }
	printf("Square Root Difference:\n");
        for (double i = 10; i < 30; i ++){
                printf("DIFFERENCE = (%.15lf)\n", Sqrt(i) - sqrt(i));
        }
	printf("Exponent Difference:\n");
        for (double i = 10; i < 30; i ++){
                printf("DIFFERENCE = (%.15lf)\n", Exp(i) - exp(i));
        } 
	printf("Log Difference:\n");
        for (double i = 10; i < 30; i ++){
                printf("DIFFERENCE = (%.15lf)\n", Log(i) - log(i));
        }
	return 0; 
}


