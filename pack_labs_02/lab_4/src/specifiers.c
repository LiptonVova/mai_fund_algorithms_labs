#include "../include/specifiers.h"

int parse_specifier(const char *format) {
    if (strlen(format) == 0) return NOT_SPECIFIER;
    else if (strlen(format) == 1) return STANDART_SPECIFIER;
    else if (strncmp(format, "Ro", 2) == 0) return ROMAN_NUMBER;
    else if (strncmp(format, "Zr", 2) == 0) return ZECKENDORF;
    else if (strncmp(format, "Cv", 2) == 0) return TEN_TO_BASE_CC_LOWER;
    else if (strncmp(format, "CV", 2) == 0) return TEN_TO_BASE_CC_UPPER;
    return STANDART_SPECIFIER;
}

void handle_specifier(error_code_t *error, char *buffer, va_list args, const int specifier, const char char_specifier) {
    if (specifier == ROMAN_NUMBER) handle_roman_number(error, buffer, args);
    else if (specifier == ZECKENDORF) handle_zeckendorf(error, buffer, args);
    else if (specifier == TEN_TO_BASE_CC_LOWER) handle_base_to_ten(error, buffer, args, false);
    else if (specifier == TEN_TO_BASE_CC_UPPER) handle_base_to_ten(error, buffer, args, true);
    else if (specifier == STANDART_SPECIFIER) handle_standart_specifier(error, buffer, args, char_specifier);
}

void handle_standart_specifier(error_code_t *error, char *buffer, va_list args, const char specifier) {
    char * endptr = NULL;
    if (specifier == 'd') {
        long result = strtol(buffer, &endptr, 10);
        int* ptr = va_arg(args, int*);
        *ptr = result;
    }
    else if (specifier == 'u') {
        unsigned long result = strtoul(buffer, &endptr, 10);
        unsigned int* ptr = va_arg(args, unsigned int*);
        *ptr = result;
    }
    else if (specifier == 'f') {
        double result = strtod(buffer, &endptr);
        float* ptr = va_arg(args, float*);
        *ptr = result;
    }
    else if (specifier == 's') {
        char* ptr = va_arg(args, char*);
        strcpy(ptr, buffer);
    }

    if (endptr == buffer) {
        *error = ERROR_STANDART_SPECIFIER;
        return;
    }

}