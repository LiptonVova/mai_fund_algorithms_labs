#ifndef NUMBER_GAMMA_H
#define NUMBER_GAMMA_H

double limit_gamma_calc(int m);
double series_gamma_calc(int k);
double equation_gamma_calc(int t, int *prime_numbers_array);

double limit_gamma(double e);
double series_gamma(double e);
double equation_gamma(double e);

#endif