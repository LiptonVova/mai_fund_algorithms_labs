#include "../include/math_function.h"


int gcd(const int a, const int b) {
    // Наибольший общий делитель
    int copy_a = abs(a);
    int copy_b = abs(b);

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


void factorization_number_impl(int number, int** result, int buf_size, error_code_t* error) {
    int index = 0; 
    int divider = 2;

    while (divider * divider <= number) {
        if (number % divider == 0) {
            if (index + 1 == buf_size) {
                buf_size *= 2;
                int* temp = (int*)realloc(*result, sizeof(int) * buf_size);
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


int* handle_factorization_number(int number, error_code_t* error) {
    // вспомогательная функция факторизации числа
    int buf_size = 1;
    int* result = (int*)malloc(sizeof(int) * buf_size); // в result[0] будет хранится колво делителей
   
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


int* factorization_number(const int number, error_code_t* error) {
    // факторизация числа
    int copy_number = number;
    if (copy_number < 0) {
        copy_number *= -1;
    }
    int* result = handle_factorization_number(copy_number, error);
    if (*error == ERROR_MALLOC) {
        return NULL;
    }
    return result;
}

