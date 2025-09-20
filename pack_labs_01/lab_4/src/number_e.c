#include "../include/number_e.h"
#include "../include/dop_functions.h"
#include <math.h>

double limit_e_calc(double n) {
    return pow(1 + 1.0/n, n);
}

double limit_e(double e) {
    double n = 0;
    double prev_value = limit_e_calc(n++);
    double result = limit_e_calc(n++);
    while (fabs(result - prev_value) >= e) {
        prev_value = result;
        result = limit_e_calc(n++);
    }
    return result;
}


double series_e_calc(int n) {
    return 1.0/factorial(n);
}


double series_e(double e) {
    int n = 0;
    double prev_value = series_e_calc(n++);
    double result = prev_value + series_e_calc(n++);

    while ( fabs(result - prev_value) >= e) {
        prev_value = result;
        result = prev_value + series_e_calc(n++);
    }   
    return result;
}

double equation_e() {
    double result = exp(1.0);
    return result;
}