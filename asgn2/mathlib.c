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
    double sum = 1.0;
    double value = 1.0;
    double term = 1.0;
    double k = 2.0;
    while (Abs(term) > EPSILON) {
        term = term * (x * x) / ((k - 1) * k);
        sum = -sum;
        value += sum * term;
	k += 2.0;
    }
    return value;
}

//square root function
double Sqrt(double x) {
    double z = 0.0;
    double y = 1.0;
    double f = 1.0; // f is the offset that is multplied with the y at the end 
    while (x > 1) {
        x /= 4.0;
        f *= 2.0;
    }
    while (Abs(y - z) > EPSILON) {
        z = y;
        y = 0.5 * (z + x / z);
    }
    return y * f;
}

//log function
double Log(double x) {
    double y = 1.0;
    double p = Exp(y); // first guess
    double e = 2.7182818284590455; // euler's constant 
    double f = 0.0; // f is the offset that is added to the y at the end 
    while (x > e) {
        f += 1.0;
        x /= e
    }
    while (Abs(p - x) > EPSILON) {
        y = y + x / p - 1;
        p = Exp(y);
    }
    return y + f;
}

