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

int gcd(const int a, const int b);
int* factorization_number(const int number, error_code_t* error);


#endif