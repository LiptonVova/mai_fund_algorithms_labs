#include "../include/number_ln2.h"
#include <math.h>


double limit_ln2_calc(double n) {
    return n * (pow(2, 1 / n) - 1);
}


double limit_ln2(double e) {
    double n = 1;
    double prev_value = limit_ln2_calc(n++);
    double result = limit_ln2_calc(n++);
    while ( fabs(result - prev_value) >= e) {
        prev_value = result;
        result = limit_ln2_calc(n++);
    }
    return result;
}

double series_ln2_calc(double n) {
    return (pow(-1, n - 1)) / n;
}

double series_ln2(double e) {
    double n = 1;
    double prev_value = series_ln2_calc(n++);
    double result = prev_value + series_ln2_calc(n++);
    while ( fabs(result - prev_value) >= e) {
        prev_value = result;
        result = prev_value + series_ln2_calc(n++);
    }
    return result;
}

double equation_ln2() {
    return log(2);
}