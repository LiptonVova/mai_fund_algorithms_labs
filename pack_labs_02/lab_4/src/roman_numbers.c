#include "../include/roman_numbers.h"



int check_roman_number(char* buffer, int size, const char* roman_literal) {
    if (strncmp(buffer, roman_literal, size) == 0) {
        return true;
    }
    return false;
}

bool validate_roman_number(error_code_t *error, int prev_value, int cur_value, int* count) {
    if (prev_value < cur_value) {
        *error = ERROR_ROMAN_NUMBER;
        return false;
    }
    else if (prev_value == cur_value) {
        (*count)++;
    }
    else {
        (*count) = 0;
    }

    if (*count == 3) {
        *error = ERROR_ROMAN_NUMBER;
        return false;
    }
    return true;
}

bool validate_right_sequance(error_code_t *error, const int prev_value, const char value) {
    // проверяет, чтобы не было таких ситуаций:
    // IXI , XLX и тд/
    // формально описывается так: если после двойного символа - идет одиночный, то в одиночном не должно быть 
    // символов, которые в этом же разряде


    // const char* roman_double_literals[] = {"CM", "CD", "XC", "XL", "IX", "IV"};
    const int roman_double_values[] = {900, 400, 90, 40, 9, 4};
    const char* roman_forbidden_literals[] = {"CD", "C", "XL", "X", "IV", "I"};

    int n = 6; 

    for (int i = 0; i < n; ++i) {
        if (roman_double_values[i] == prev_value) {
            for (int j = 0; j < strlen(roman_forbidden_literals[i]); ++j) {
                if (roman_forbidden_literals[i][j] == value) {
                    *error = ERROR_ROMAN_NUMBER;
                    return false;
                }
            }
            return true;
        }
    }
    *error = ERROR_ROMAN_NUMBER;
    return false;
}

bool all_validate(error_code_t *error, const int size_p_value, const int p_value, const int size, const int value, int *count, const char* char_value ) {
    if (!validate_roman_number(error, p_value, value, count)) {
        return false;
    }

    if (size_p_value == 2 && size == 1) {
        if (!validate_right_sequance(error, p_value, char_value[0])) {
            return false;
        }
    }

    else if (size_p_value == 2 && size == 2) {
        if (p_value == value) {
            return false;
        }
    }
    return true;
}

bool handle_roman_number_impl(error_code_t *error, char *buffer,  int *answer) {
    const char* roman_literals[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    const int roman_values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};

    bool flag = false;
    int prev_value = INT_MAX;
    int length_prev_value = 0;
    int count = 0;

    int n = 13;

    while (*buffer != '\0') {
        flag = false;
        for (int i = 0; i < n; ++i) {
            int size_cur_literal = strlen(roman_literals[i]);
            if (check_roman_number(buffer, size_cur_literal, roman_literals[i])) {
                int value = roman_values[i];

                if (!all_validate(error, length_prev_value, prev_value, size_cur_literal, value, &count, roman_literals[i])) {
                    return false;
                }

                buffer += size_cur_literal;
                *answer += value;
                length_prev_value = size_cur_literal;
                prev_value = value;
                flag = true;
                break;
            }
        }

        if (!flag) {
            *error = ERROR_ROMAN_NUMBER;
            return false;
        }
    }
    return true;
}


void handle_roman_number(error_code_t *error, char* buffer, va_list args) {
    int answer = 0;

    bool flag = handle_roman_number_impl(error, buffer, &answer);
    if (!flag) {
        return;
    }

    int* ptr = va_arg(args, int*);
    *ptr = answer;
}