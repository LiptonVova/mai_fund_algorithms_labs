#include "../include/math_function.h"


long long gcd(const long long a, const long long b) {
    // Наибольший общий делитель
    long long copy_a = abs(a);
    long long copy_b = abs(b);

    while ( copy_a != 0 && copy_b != 0) {
        if (copy_a > copy_b) {
            copy_a = copy_a % copy_b;
        }
        else {
            copy_b = copy_b % copy_a;
        }
    }

    return copy_a + copy_b;
}


void factorization_number_impl(long long number, long long** result, int buf_size, error_code_t* error) {
    int index = 0; 
    long long divider = 2;

    while (divider * divider <= number) {
        if (number % divider == 0) {
            if (index + 1 == buf_size) {
                buf_size *= 2;
                long long* temp = (long long*)realloc(*result, sizeof(long long) * buf_size);
                if (!temp) {
                    *error = ERROR_MALLOC;
                    return;
                }
                *result = temp;
            }
            (*result)[++index] = divider;
            number /= divider;
            continue; 
        }
        ++divider;
    }
    (*result)[++index] = number;
    (*result)[0] = index;
}


long long* handle_factorization_number(long long number, error_code_t* error) {
    // вспомогательная функция факторизации числа
    int buf_size = 1;
    long long* result = (long long*)malloc(sizeof(long long) * buf_size); // в result[0] будет хранится колво делителей
   
    if (!result) {
        *error = ERROR_MALLOC;
        return NULL;
    }

    if (number == 0 || number == 1) {
        result[0] = 0;
        return result;
    }

    factorization_number_impl(number, &result, buf_size, error);
    if (*error == ERROR_MALLOC) {
        return NULL;
    }    
    return result;
}


long long* factorization_number(const long long number, error_code_t* error) {
    // факторизация числа
    long long copy_number = number;
    if (copy_number < 0) {
        copy_number *= -1;
    }
    long long* result = handle_factorization_number(copy_number, error);
    if (*error == ERROR_MALLOC) {
        return NULL;
    }
    return result;
}

