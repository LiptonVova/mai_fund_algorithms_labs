#include "../include/number_pi.h"
#include "../include/dop_functions.h"
#include <math.h>
#include <stdio.h>

double limit_pi_calc(int n) {
    double chislitel = pow( pow(2, n) * factorial(n) , 4);
    double znamenatel = n * pow(factorial(2*n), 2);
    double result = chislitel/znamenatel;
    return result;
}


double limit_pi(double e) {
    int n = 1;
    double prev_value = limit_pi_calc(n++);
    double result = limit_pi_calc(n++);

    int count_iterations = 0;
    while ( fabs(result - prev_value) >= e) {
        prev_value = result;
        result = limit_pi_calc(n++);
        ++count_iterations;
        if (count_iterations == 19) {
            break;
        }
    }
    return result;
}

double series_pi_calc(int n) {
    return (pow(-1, n - 1))/(2.0 * n - 1);
}

double series_pi(double e) {
    int n = 1;
    double prev_value = series_pi_calc(n++);
    double result = prev_value + series_pi_calc(n++);
    while ( fabs(result - prev_value) >= e) {
        prev_value = result;
        result = series_pi_calc(n++) + prev_value;
    }
    return 4 * result;
}


double equation_pi() {
    return acos(-1);
}
 