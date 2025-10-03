#include "../include/check_finite_fraction.h"


bool define_finite_fraction_impl(int* factor_denom, int* factor_num_system) {
    int count_denom = factor_denom[0];
    int count_number_system = factor_num_system[0];

    bool flag = false;
    for (int i = 1; i <= count_denom; ++i) {
        flag = false;
        for (int j = 1; j <= count_number_system; ++j) {
            if (factor_denom[i] == factor_num_system[j]) {
                flag = true;
                break;
            }
        }
        if (!flag) {
            break;
        }
    }
    return flag || count_denom == 0;
}

bool define_finite_fraction(const int number_system, const double number, error_code_t *error) {
    // определить, можно ли представить в виде конечной дроби
    int numerator = 0;
    int denominator = 0;
    numerator_and_denominator_from_fraction(number, &numerator, &denominator, error);
    if (*error == ERROR_STRTOL) {
        return false;
    }

    int* reducing_fraction = reducing_a_fraction(numerator, denominator, error);
    if (*error == ERROR_DIVIDE_ZERO || *error == ERROR_MALLOC) {
        return false;
    }

    int* factorization_denominator = factorization_number(reducing_fraction[1], error);
    int* factorization_number_system = factorization_number(number_system, error);

    if (*error == ERROR_MALLOC) {
        return false;
    }

    return define_finite_fraction_impl(factorization_denominator, factorization_number_system);
}


bool* define_list_of_finite_fraction(const int number_system, error_code_t *error, const int n, ...) {
    // определить можно ли представить в конечной дроби произвольное колво аргументов
    va_list list_of_arguments;
    va_start(list_of_arguments, n);

    bool* result_list = (bool*)malloc(sizeof(bool) * n);
    if (!result_list) {
        *error = ERROR_MALLOC;
        return NULL;
    }
    bool result = false;
    for (int i = 0; i < n; ++i) {
        const double number = va_arg(list_of_arguments, double);
        double copy_number = number;
        if (number < 0) {
            copy_number *= -1;
        }
        result = define_finite_fraction(number_system, copy_number, error);
        if (*error != SUCCESS) {
            return NULL;
        }
        result_list[i] = result;
    }
    va_end(list_of_arguments);
    return result_list;
}