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
	return 0; 
}


