#include "../include/translate_base_to_ten.h"


bool validate_base_to_ten(error_code_t *error, int answer, char *end) {
    if (answer > INT_MAX) {
        *error = ERROR_TRANSLATE_BASE_TO_TEN;
        return false;
    }
    else if (answer < INT_MIN) {
        *error = ERROR_TRANSLATE_BASE_TO_TEN;
        return false;
    }
    if (*end != '\0') {
        *error = ERROR_TRANSLATE_BASE_TO_TEN;
        return false;
    }
    return true;
}

bool validate_upper_symbols(error_code_t *error, char*buffer, bool upper) {
    if (*buffer == '-' || *buffer == '+') {
        ++buffer;
    }
    char letter_a = upper ? 'A' : 'a';
    char letter_z = upper ? 'Z' : 'z';
    while (*buffer != '\0') {
        if (*buffer >= '0' && *buffer <= '9') {
            buffer++;
            continue;
        }
        else if (*buffer >= letter_a && *buffer <= letter_z) {
            buffer++;
            continue;
        }
        else {
            *error = ERROR_TRANSLATE_BASE_TO_TEN;
            return false;
        }
    }
    return true;
}

void handle_base_to_ten(error_code_t *error, char* buffer, va_list args, bool upper) {
    int answer = 0;
    int* ptr = va_arg(args, int*);
    int base = va_arg(args, int);
    if (base < 2 || base > 36) {
        base = 10;
    }

    char* end;
    answer = strtol(buffer, &end, base);
    if (!validate_base_to_ten(error, answer, end)) {
        return;
    }

    if (!validate_upper_symbols(error, buffer, upper)) {
        return;
    }

    *ptr = answer;
}