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

void handle_specifier(error_code_t *error, char *buffer, va_list args, const int specifier) {
    if (specifier == ROMAN_NUMBER) handle_roman_number(error, buffer, args);
    else if (specifier == ZECKENDORF) handle_zeckendorf(error, buffer, args);
    else if (specifier == TEN_TO_BASE_CC_LOWER) handle_base_to_ten(error, buffer, args, false);
    else if (specifier == TEN_TO_BASE_CC_UPPER) handle_base_to_ten(error, buffer, args, true);
}

void parse_standart_specifier(error_code_t *error, const char**format,  char* char_specifier) {
    // записывает спецификатор из format

    char specifier[32] = "%";
    int len_specifier = 1;

    while (**format && len_specifier < 30) {
        char c = **format; 
        specifier[len_specifier++] = c;
        (*format)++;

        if (isalpha(c) && c != 'l'&& c != 'L' && c != 'h' && c != 'z' && c != 't' && c != 'j') {
            break;
        }
    }

    specifier[len_specifier] = '\0';
    char_specifier[0] = '\0';
    strcpy(char_specifier, specifier);
}