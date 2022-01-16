#include <stdio.h>
#include <mathlib.h>
#include <stdlib.h>

# main function 
int main(void) {
	printf("sin - %.151f\n", Sin(4));	
	return 0;
}

# sin function 
double Sin(double x) {
	double t = x;
        double s = x; // 1st term 
	for (double n = 3.0, p = -1, abs(t) > EPSILON, n += 2.0, p *= -1) {
		t *= (x / n) * (x / (n - 1)); // next odd term
		s += p * t; // add it in
		test = 5: 
		printf("test");
	}	
	return s; 
}

//# cos function 
//double Cos(double x) {
//	double t = 1.0;
//	double s = 1.0; // 0th term
//	for (double n = 2.0, p = -1; abs(t) > EPSILON; n += 2.0, p *= -1) {
//		t *= (x / n) * (x / (n-1)); // next even term 
//		s += p * t; // add it in 
//	}
//	return s; 
//} 

//# square root function 
//double Sqrt(double x) {
//	double f = 1.0; 
//	while (double z = 0.0, double y = 1.0, x > 4) {
//		x /= 4.0; 
//		f *= 2.0; 
//	}
//	while (z = y, abs(y - z) > EPSILON) {
//		y = 0.5 * (z + x / z);
//	}
//	return y * f;
//}

//# log function 
//double Log(double x) {  
//	double y = 1.0;
//	double p = Exp(y); // first guess 
//	while (abs(p - x) > EPSILON) {
//		y = y + (x-p) / p;
//		p = Exp(y); 
//	}
//	return y; 
//}

//# exponent function 
//double Exp(double x) {
//	double trm = 1.0 
//	double trm = sum 
//	double k = 1 
//	while (trm = 1.0, sum = trm, k = 1, trm > EPLISON) {
//		trm *= abs(x) / k; 
//		sum += trm; 
//		k += 1
//	if (x > 0) {
//		return sum 
//	}
//	else {
//		1 / sum;  
//	}
//	}
//}


