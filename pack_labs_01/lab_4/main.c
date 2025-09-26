#include <stdio.h>

#include "include/number_e.h"
#include "include/number_gamma.h"
#include "include/number_ln2.h"
#include "include/number_pi.h"
#include "include/number_sqrt_2.h"
#include "include/dop_functions.h"


int main() {
    double e = 0.00000001;

    printf("Точность равна %.8lf\n", e);

    double result_e_1 = limit_e(e); 
    double result_e_2 = series_e(e);
    double result_e_3 = equation_e(e);

    printf("число e равно: %lf, %lf, %lf\n", result_e_1, result_e_2, result_e_3);

    double result_pi_1 = limit_pi(e);
    double result_pi_2 = series_pi(e);
    double result_pi_3 = equation_pi(e);

    printf("число пи равно: %lf, %lf, %lf\n", result_pi_1, result_pi_2, result_pi_3);


    double result_ln2_1 = limit_ln2(e);
    double result_ln2_2 = series_ln2(e);
    double result_ln2_3 = equation_ln2(e);

    printf("число ln2 равно: %lf, %lf, %lf\n", result_ln2_1, result_ln2_2, result_ln2_3);

    double result_sqrt2_1 = limit_sqrt2(e);
    double result_sqrt2_2 = series_sqrt2(e);
    double result_sqrt2_3 = equation_sqrt2(e);

    printf("число sqrt2 равно: %lf, %lf, %lf\n", result_sqrt2_1, result_sqrt2_2, result_sqrt2_3);


    double result_gamma_1 = limit_gamma(e);
    double result_gamma_2 = series_gamma(e);
    double result_gamma_3 = equation_gamma(e);

    printf("число gamma равно: %lf, %lf, %lf\n", result_gamma_1, result_gamma_2, result_gamma_3); 

    return 0;
}