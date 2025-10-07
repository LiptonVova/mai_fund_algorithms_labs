#ifndef ADDITIONAL_FUNCTIONS_H
#define ADDITIONAL_FUNCTIONS_H

#include <string.h>
#include <stdio.h>
#include <stdbool.h>

typedef enum {
    SUCCESS,
    ERROR_TRANSLATE_BASE_TO_TEN = -1,
    ERROR_UNKNOWN_MEMORY_TYPE = -2,
} error_code_t ;


void generate_fibonacci(const unsigned int num, unsigned int* fib, int* count);
void int_to_roman(int num, char* buffer);
void zeckendorf(const unsigned int num, char* buffer);
void translate_ten_to_base_cc(const int num, const int base, char* buffer, bool upper);
int* translate_base_to_ten_cc(const char*num, const int base, int* result, bool upper);
void memory_dump(error_code_t *error, const unsigned char*bytes, unsigned char* buffer, const char type);

#endif