#ifndef SPECIFIERS_H
#define SPECIFIERS_H

#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include "additional_functions.h"

typedef enum {
    ROMAN_NUMBER = 1,
    ZECKENDORF = 2,
    TEN_TO_BASE_CC_LOWER = 3,
    TEN_TO_BASE_CC_UPPER = 4,
    BASE_TO_TEN_CC_LOWER = 5,
    BASE_TO_TEN_CC_UPPER = 6,
    MEMORY_DUMP = 7,

    NOT_SPECIFIER = -2,
    STANDART_SPECIFIER = -1,
} type_specifiers ;


int hanlde_specifier(error_code_t *error, int specifier, char *result, const char **format, va_list args);
int parse_specifier(const char *format);
void handle_standart_specifier(char* str_specifier, const char **format, va_list args);
void handle_roman_number(char *result, va_list args);
void handle_zeckendorf(char *result, va_list args);
void handle_ten_to_base_cc_lower(char *result, va_list args);
void handle_ten_to_base_cc_upper(char *result, va_list args);
void handle_base_to_ten_cc_lower(error_code_t *error, char *result, va_list args);
void handle_base_to_ten_cc_upper(error_code_t *error, char *result, va_list args);
void handle_memory_dump(error_code_t *error, char *result, va_list args, const char *format);


#endif