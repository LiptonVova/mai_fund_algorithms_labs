#include <stdio.h>
#include "include/check_finite_fraction.h"

int main() {
    error_code_t error = SUCCESS;
    
    int n = 5;
    double list[] = {0.2, -0.015625, 1.0/3.0, 131.421, 0, 123.4213};
    int number_system = 2;
    bool* result = define_list_of_finite_fraction(number_system, &error, n, list[0], list[1], list[2], list[3], list[4]);

    switch (error) {
        case ERROR_DIVIDE_ZERO:
            printf("Деление на ноль\n");
            return ERROR_DIVIDE_ZERO;
            break;
        case ERROR_MALLOC:
            printf("Ошибка выделения памяти\n");
            return ERROR_MALLOC;
            break;
        case ERROR_STRTOL:
            printf("Ошибка при переводе из string в int\n");
            return ERROR_STRTOL;
            break;
    }


    for (int i = 0; i < n; ++i) {
        if (result[i] == false) {
            printf("Число %lf не может быть представлено в конечной дроби в системе счисления %d\n", list[i], number_system);
        }
        else {
            printf("Число %lf может быть представлено в конечной дроби в системе счисления %d\n", list[i], number_system);
        }
    }

    return SUCCESS;
}