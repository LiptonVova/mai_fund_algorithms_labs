#include "../include/specifiers.h"

int hanlde_specifier(error_code_t *error, int specifier, char *result, const char **format, va_list args) {
    if (specifier == ROMAN_NUMBER) handle_roman_number(result, args);
    else if (specifier == ZECKENDORF) handle_zeckendorf(result, args);
    else if (specifier == TEN_TO_BASE_CC_LOWER) handle_ten_to_base_cc_lower(result, args); 
    else if (specifier == TEN_TO_BASE_CC_UPPER) handle_ten_to_base_cc_upper(result, args); 
    else if (specifier == BASE_TO_TEN_CC_LOWER) handle_base_to_ten_cc_lower(error, result, args);
    else if (specifier == BASE_TO_TEN_CC_UPPER) handle_base_to_ten_cc_upper(error, result, args);
    else if (specifier == MEMORY_DUMP) handle_memory_dump(error, result, args, *format);
    else if (specifier == NOT_SPECIFIER) strcpy(result, "%");
    else if (specifier == STANDART_SPECIFIER) handle_standart_specifier(result, format, args);

    if (specifier > 0) {
        *format += 2;
        return strlen(result);
    }
    return 0;

}

int parse_specifier(const char *format) {
    if (strlen(format) == 0) {
        return -2;
    }
    else if (strlen(format) == 1) {
        return -1;
    }

    if (strncmp(format, "Ro", 2) == 0) return 1;
    else if (strncmp(format, "Zr", 2) == 0) return 2;
    else if (strncmp(format, "Cv", 2) == 0) return 3;
    else if (strncmp(format, "CV", 2) == 0) return 4;
    else if (strncmp(format, "to", 2) == 0) return 5;
    else if (strncmp(format, "TO", 2) == 0) return 6;
    else if (strncmp(format, "m", 1) == 0) {
        const char c = *(format + 1); 
        if (c == 'i' || c == 'u' || c == 'd' || c == 'f') {
            return 7;
        }
    };    
    return -1;
}

void handle_standart_specifier(char* str_specifier, const char **format, va_list args) {
    char specifier[32] = "%";
    int specifier_len = 1;

    while (**format && specifier_len < 30) {
        char c = **format;
        specifier[specifier_len++] = c;
        (*format)++;

        if (isalpha((unsigned char)c) && c != 'l' && c != 'L' && c != 'h' && c != 'z' && c != 't' && c != 'j') {
            break;
        } 
    }

    specifier[specifier_len] = '\0';
    str_specifier[0] = '\0';
    strcpy(str_specifier, specifier);
}

void handle_roman_number(char *result, va_list args) {
    int res = va_arg(args, int);
    int_to_roman(res, result);
}

void handle_zeckendorf(char *result, va_list args) {
    unsigned int res = va_arg(args, unsigned int);
    zeckendorf(res, result);
}

void handle_ten_to_base_cc_lower(char *result, va_list args) {
    const int num = va_arg(args, int);
    const int base = va_arg(args, int);
    translate_ten_to_base_cc(num, base, result, false);
}

void handle_ten_to_base_cc_upper(char *result, va_list args) {
    const int num = va_arg(args, int);
    const int base = va_arg(args, int);
    translate_ten_to_base_cc(num, base, result, true);
}

void handle_base_to_ten_cc_lower(error_code_t *error, char *result, va_list args) {
    const char*num = va_arg(args, char*);
    const int base = va_arg(args, int);
    int number_ten_cc = 0;
    int* tmp = translate_base_to_ten_cc(num, base, &number_ten_cc, false);
    if (tmp == NULL) {
        *error = ERROR_TRANSLATE_BASE_TO_TEN;
        return;
    }
    sprintf(result, "%d", number_ten_cc);
}

void handle_base_to_ten_cc_upper(error_code_t *error, char *result, va_list args) {
    const char*num = va_arg(args, char*);
    const int base = va_arg(args, int);
    int number_ten_cc = 0;
    int* tmp = translate_base_to_ten_cc(num, base, &number_ten_cc, true);
    if (tmp == NULL) {
        *error = ERROR_TRANSLATE_BASE_TO_TEN;
        return;
    }
    sprintf(result, "%d", number_ten_cc);
}

void handle_memory_dump(error_code_t *error, char *result, va_list args, const char *format) {
    const int num =  va_arg(args, int);
    const unsigned char* bytes = (unsigned char*)(&num);
    memory_dump(error, bytes, result, *(format+1));
}



