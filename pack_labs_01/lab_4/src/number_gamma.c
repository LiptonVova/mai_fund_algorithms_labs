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
        if (m == 40) {
            break;
        }
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

    while ( fabs(result - prev_value) >= e   || fabs(prev_value - prev_prev_value) >= e) {
        
        prev_prev_value = prev_value;
        prev_value = result;
        result = prev_value + series_gamma_calc(k++);
    }
    return (equation_pi(e) * equation_pi(e))/(-6) + result;
}

double equation_gamma_calc(int t, int *prime_numbers_array) {
    double proisvedenie = 1.0;
    for (int p = 2; p < t; p++) {
        if (prime_numbers_array[p] == 0) {
            proisvedenie *= ((p - 1.0)/ ((double)(p)));
        }
    }
    return log(t) * proisvedenie;
}


double equation_gamma(double e) {
    int t_max = 1e6;
    int * prime_numbers_array = prime_numbers(t_max);
    if (!prime_numbers_array) {
        return -1;
    }

    double result_limit = equation_gamma_calc(t_max, prime_numbers_array);    
    
    double l = 0;
    double r = 1;
    double mid;

    while (fabs(r - l) >= e) {
        mid = (l + r) / 2.0;
        if (exp(-mid) - result_limit > 0) {
            l = mid;
        }
        else {
            r = mid;
        }
    }

    free(prime_numbers_array);
    return (l + r) / 2.0;

}