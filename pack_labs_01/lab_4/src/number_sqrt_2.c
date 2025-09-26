#include "../include/number_sqrt_2.h"
#include <math.h>


double limit_sqrt2_calc(double x_n) {
    return x_n - (x_n * x_n) / 2 + 1;
}


double limit_sqrt2(double e) {
    double prev_value = -0.5;
    double result = limit_sqrt2_calc(prev_value);
    while ( fabs(result - prev_value) >= e ) {
        prev_value = result;
        result = limit_sqrt2_calc(prev_value);
    }
    return result;
}

double series_sqrt2_calc(double k) {
    return pow(2, pow(2, -k));
}

double series_sqrt2(double e) {
    double k = 2;
    double prev_value = series_sqrt2_calc(k++);
    double result = prev_value * series_sqrt2_calc(k++);
    while (fabs(result - prev_value) >= e) {
        prev_value = result;
        result = prev_value * series_sqrt2_calc(k++);
    }
    return result;
}

double equation_sqrt2(double e) {
    double l = 1;
    double r = 3;

    double mid;
    while (fabs(r - l) >= e) {
        mid = (l + r) / 2.0;
        if (mid * mid - 2 > 0) {
            r = mid;
        }
        else {
            l = mid;
        }
    }
    return (l + r)/2.0;
}