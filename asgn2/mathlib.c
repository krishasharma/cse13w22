#include <stdio.h>
#include "mathlib.h"
#include <stdlib.h>

#define EPSILON 1e-14 

//exponent function
double Exp(double x) {
        double trm = 1.0;
        double sum = trm;
        double k = 1;
        while (trm > EPSILON) {
                trm *= Abs(x) / k;
                sum += trm;
                k += 1;
        }
	return sum; 	
}

//sin function
double Sin(double x) {
        double s = 1.0;
        double v = x;
        double t = x;
        double k = 3.0;
        while (Abs(t) > EPSILON) {
                t = t * (x * x) / ((k - 1) * k);
                s = -s;
                v += s * t;
                k += 2.0;
        }
        return v;
}

//cos function 
double Cos(double x) {
        double sum = 0.0;
        double value = x;
        double term = x;
        double k = 2.0;
        while (Abs(term) > EPSILON) {
                term = term * (x * x) / ((k - 1) * k);
                sum = -sum;
                value += sum * term;
                k += 2.0;
        }
        return value;
}
/*
//square root function
double Sqrt(double x) {
        double z = 0.0;
        double y = 1.0;
        while (Abs(y - z) > EPSILON) {
                z = y;
                y = 0.5 * (z + x / z);
        }
        return y;
}

//log function
double Log(double x) {
        double y = 1.0;
        double p = Exp(y); // first guess
        while (Abs(p - x) > EPSILON) {
                y = y + x / p - 1;
                p = Exp(y);
        }
        return y;
}
*/
