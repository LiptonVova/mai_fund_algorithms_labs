#ifndef MATH_FUNCTION_H
#define MATH_FUNCTION_H

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

typedef enum {
    SUCCESS,
    ERROR_DIVIDE_ZERO,
    ERROR_MALLOC,
    ERROR_STRTOL
} error_code_t;

long long gcd(const long long a, const long long b);
long long* factorization_number(const long long number, error_code_t* error);


#endif