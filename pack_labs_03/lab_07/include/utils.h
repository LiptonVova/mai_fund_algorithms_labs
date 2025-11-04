#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef enum {
    ASSIGNMENT,
    PRINT,
    ERROR_EXPRESSION,
} TypeOperation;

void print_usage();

void delete_spaces_and_upper_case(char* str);

void define_type_operation(char* str, TypeOperation* type_operation);

int fast_raise_to_the_power(const int base, const int exponent);

#endif