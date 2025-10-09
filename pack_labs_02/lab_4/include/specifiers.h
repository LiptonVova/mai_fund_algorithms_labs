#ifndef SPECIFIERS_H
#define SPECIFIERS_H

#include "additional_functions.h"
#include "roman_numbers.h"
#include "zeckendorf.h"
#include "translate_base_to_ten.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>

typedef enum {
    ROMAN_NUMBER = 1,
    ZECKENDORF = 2,
    TEN_TO_BASE_CC_LOWER = 3,
    TEN_TO_BASE_CC_UPPER = 4,
    NOT_SPECIFIER = -2,
    STANDART_SPECIFIER = -1,
} type_specifiers;


int parse_specifier(const char *format);
void handle_specifier(error_code_t *error, char *buffer, va_list args, const int specifier);
void handle_roman_number(error_code_t *error, char* buffer, va_list args);
void parse_standart_specifier(error_code_t *error, const char**format,  char* char_specifier);


#endif