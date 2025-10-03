#include "../include/fraction.h"


bool validate_fraction(const int denominator, error_code_t* error) {
    if (denominator == 0) {
        *error = ERROR_DIVIDE_ZERO;
        return false;
    }
    return true;
}

void reducing_a_fraction_impl(int* result) {
    int cur_gcd = gcd(result[0], result[1]);
    while (cur_gcd != 1) {
        result[0] = result[0] / cur_gcd;
        result[1] = result[1] / cur_gcd;
        
        cur_gcd = gcd(result[0], result[1]);
    }
}

int* reducing_a_fraction(const int numerator, const int denominator, error_code_t* error) {
    // функция сокращения дроби
    if (!validate_fraction(denominator, error)) {
        return NULL;
    }
    int* result = (int*)malloc(sizeof(int) * 2);
    if (!result) {
        *error = ERROR_MALLOC;
        return NULL;
    }
    result[0] = numerator;
    result[1] = denominator; 

    reducing_a_fraction_impl(result);
    return result;
}


void double_to_string(char* str, const double number) {
    sprintf(str, "%lf", number);

    int index = strlen(str);
    for (int i = 1; i < strlen(str); ++i) {
        if (str[i] == '0' && index == strlen(str)) {
            index = i;
        } else {
            index = strlen(str);
        }
    }
    str[index] = '\0'; // убрать ненужные нули в конце
}

void divide_left_and_right_partition(char* str, char* left, char* right, char* ptr_comma) {
    // разделить дробь на левую и правую часть от запятой
    // ptr_comma - указатель на '.'
    // str - указатель на число
    int len = strlen(str);
    int index = ptr_comma - str;
    strncpy(left, str, index);
    left[index] = '\0';

    strncpy(right, ptr_comma + 1, len - index);
    right[len-index] = '\0';
}


bool convert_char_to_int(int* left, int* right, char* char_left, char* char_right, error_code_t *error) {
    char* end_ptr;
    *left = strtol(char_left, &end_ptr, 10);
    if (*end_ptr != '\0') {
        *error = ERROR_STRTOL;
        return false;
    }

    *right = strtol(char_right, &end_ptr, 10);
    if (*end_ptr != '\0') {
        *error = ERROR_STRTOL;
        return false;
    }
    return true;
}


void num_and_denom_impl(char* char_right, int left, int right, int* num, int* denom) {
    int int_denominator = 1;
    for (int i = 0; i < strlen(char_right); ++i) {
        int_denominator *= 10;
    }

    *num = int_denominator * left + right;
    *denom = int_denominator;
}


void numerator_and_denominator_from_fraction(const double number, int*num, int*denom, error_code_t* error) {
    // разделить double на числитель и знаменатель
    char str[50];
    int len = strlen(str);
    double_to_string(str, number);
    

    char* ptr_comma = strstr(str, ".");
    if (ptr_comma == NULL) {
        *num = number;
        *denom = 1;
        return;
    }
    
    char char_left[50];
    char char_right[50];
    
    divide_left_and_right_partition(str, char_left, char_right, ptr_comma);
    
    int int_left, int_right;

    if (!convert_char_to_int(&int_left, &int_right, char_left, char_right, error)) {
        return;
    }

    num_and_denom_impl(char_right, int_left, int_right, num, denom);
}
