#include "../include/number_gamma.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/dop_functions.h"
#include "../include/number_pi.h"

double limit_gamma_calc(int m) {
    double summa = 0;
    for (int k = 1; k <= m; ++k) {
        double sochetaniya = (factorial(m))/(factorial(m - k) * factorial(k));

        summa += (sochetaniya * (pow(-1, k)/k)) * log(factorial(k));
    }
    return summa;
}

double limit_gamma(double e) {
    int m = 1;
    double prev_value = limit_gamma_calc(m++);
    double result = limit_gamma_calc(m++);

    while (fabs(result - prev_value) >= e) {
        prev_value = result;
        result = limit_gamma_calc(m++);
    }
    return result;
}


double series_gamma_calc(int k) {
    int sqrt_k = sqrt(k);
    return (1.0/(sqrt_k * sqrt_k) - 1.0/k);
}


double series_gamma(double e) {
    int k = 2;
    double prev_prev_value = series_gamma_calc(k++);
    double prev_value = prev_prev_value + series_gamma_calc(k++);
    double result = prev_value + series_gamma_calc(k++);

    while ( fabs(result - prev_value) >= e/1000000   || fabs(prev_value - prev_prev_value) >= e/1000000) {
        
        prev_prev_value = prev_value;
        prev_value = result;
        result = prev_value + series_gamma_calc(k++);
    }
    return (equation_pi() * equation_pi())/(-6) + result;
}

double equation_gamma_calc(int t, int *prime_numbers_array, int count, double e) {
    double proisvedenie = 1.0;
    for (int i = 0; i < count; i++) {
        double p = prime_numbers_array[i];
        if ( fabs(p - t) <= e) {
            break;    
        }
        proisvedenie *= ((p-1)/p);
    }
    return log(t) * proisvedenie;
}


double equation_gamma(double e) {
    int t = 1;
    int count = 150;
    int * prime_numbers_array = prime_numbers(count);
    double prev_value = equation_gamma_calc(t++, prime_numbers_array, count, e);
    double result = equation_gamma_calc(t++, prime_numbers_array, count, e);

    while (fabs(result - prev_value) >= e) {
        prev_value = result;
        result = equation_gamma_calc(t++, prime_numbers_array, count, e);
    }
    free(prime_numbers_array);
    return -log(result);

}