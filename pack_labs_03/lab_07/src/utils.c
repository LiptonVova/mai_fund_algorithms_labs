#include "../include/utils.h"


void print_usage() {
    printf("./main.out [input_file] [log_file]\n");
}

void delete_spaces_and_upper_case(char* str) {
    size_t index = 0;
    for (size_t i = 0; i < strlen(str); ++i) {
        if (str[i] != ' ' && str[i] != '\n') str[index++] = toupper(str[i]);
    }
    str[index] = '\0';
}

void define_print(char* str, TypeOperation* type_operation) {
    // определить валидная ли команда print

    // PRINT(X) - минимальная команда print. Длина - 8
    const int min_length = 8;
    if (strlen(str) < min_length) {
        *type_operation = ERROR_EXPRESSION;
        return;
    }

    if ((strncmp(str, "PRINT(", 6) == 0 && str[strlen(str) - 1] == ')')) {
        // если начало строки PRINT( и конец строки )
        *type_operation = PRINT;
        return;
    }
    *type_operation = ERROR_EXPRESSION; 
}

void define_type_operation(char* str, TypeOperation* type_operation) {
    // определить тип операции
    
    // A=1 - минимальная команда. Длина - 3
    const int min_length = 3;
    if (strlen(str) < min_length) { 
        *type_operation = ERROR_EXPRESSION;
        return;
    }

    if (str[0] == 'P') {
        // это либо команда PRINT, либо переменной P что то присваивается
        
        if (str[1] == '=') {
            *type_operation = ASSIGNMENT;
            return;
        }

        define_print(str, type_operation);

    }
    else if (str[0] >= 'A' && str[0] <= 'Z' && str[1] == '=') {
        // значит это присваивание
        *type_operation = ASSIGNMENT;
    }
    else {
        *type_operation = ERROR_EXPRESSION;
    }
}

int fast_raise_to_the_power(const int base, const int exponent) {
    // base - основание степени
    // exponent - показатель степени

    int result = 1;
    int n = exponent;
    int copy_base = base;

    while (n > 0) {
        if (n & 1) { // единица на конце
            result *= copy_base;
        }

        copy_base *= copy_base; // возводим в квадрат base
        n = n >> 1; // сдигаем вправо, чтобы обработать последний бит        
    }
    return result;
}