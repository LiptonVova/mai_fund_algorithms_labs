#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "include/output.h"
#include "include/check.h"
#include "include/solve.h"


enum {
    SUCCESS,
    ERROR_WITHOUT_PARAMETRS,
    ERROR_INVALID_PARAMETR,
    ERROR_INVALID_ARGUMENT,
    ERROR_UNKNOWN_PARAMETR,
};


int main(int argc, char * argv[]) {
    if (argc <= 1) {
        print_usage();
        return ERROR_WITHOUT_PARAMETRS;
    }

    if (strcmp(argv[1], "-q") == 0 || strcmp(argv[1], "/q") == 0) {
        if (argc != 6) {
            print_usage();
            return ERROR_INVALID_PARAMETR;
        }  

        int flag_e = check_double_number(argv[2]);
        int flag_1 = check_double_number(argv[3]);
        int flag_2 = check_double_number(argv[4]);
        int flag_3 = check_double_number(argv[5]);

        if (!flag_e || !flag_1 || !flag_2 || !flag_3) {
            print_usage();
            return ERROR_INVALID_ARGUMENT;
        }

        char* endptr_e;
        char* endptr_1;
        char* endptr_2;
        char* endptr_3;

        double number_e = strtod(argv[2], &endptr_e);
        double number_1 = strtod(argv[3], &endptr_1);
        double number_2 = strtod(argv[4], &endptr_2);
        double number_3 = strtod(argv[5], &endptr_3);

        double * result_1 = solve_quadratic_equation(number_e, number_1, number_2, number_3);
        double * result_2 = solve_quadratic_equation(number_e, number_1, number_3, number_2);
        double * result_3 = solve_quadratic_equation(number_e, number_2, number_1, number_3);
        double * result_4 = solve_quadratic_equation(number_e, number_2, number_3, number_1);
        double * result_5 = solve_quadratic_equation(number_e, number_3, number_1, number_2);
        double * result_6 = solve_quadratic_equation(number_e, number_3, number_2, number_1);
        
        int precision = 1;
        double number_e_copy = number_e;
        while (number_e_copy < 1) {
            ++precision;
            number_e_copy *= 10;
        }

        print_quadratic_equation(result_1, precision, number_1, number_2, number_3);
        print_quadratic_equation(result_2, precision, number_1, number_3, number_2);
        print_quadratic_equation(result_3, precision, number_2, number_1, number_3);
        print_quadratic_equation(result_4, precision, number_2, number_3, number_1);
        print_quadratic_equation(result_5, precision, number_3, number_1, number_2);
        print_quadratic_equation(result_6, precision, number_3, number_2, number_1);

        free(result_1);
        free(result_2);
        free(result_3);
        free(result_4);
        free(result_5);
        free(result_6);
    }

    else if (strcmp(argv[1], "-m") == 0 || strcmp(argv[1], "/m") == 0) {
        if (argc != 4) {
            print_usage();
            return ERROR_INVALID_PARAMETR;
        }
        
        int flag_1 = check_int_number(argv[2]);
        int flag_2 = check_int_number(argv[3]);

        if (!flag_1 || !flag_2) {
            print_usage();
            return ERROR_INVALID_ARGUMENT;
        }

        int number_1 = atoi(argv[2]);
        int number_2 = atoi(argv[3]);

        if (number_1 == 0 || number_2 == 0) {
            printf("Ошибка: Введите ненулевые значения\n\n");
            print_usage();
            ERROR_INVALID_ARGUMENT;
        }   

        if (number_1 % number_2 == 0) {
            printf("%d делится на %d\n", number_1, number_2);
        }
        else {
            printf("%d не делится на %d\n", number_1, number_2);
        }
    }

    else if (strcmp(argv[1], "-t") == 0 || strcmp(argv[1], "/t") == 0) {
        if (argc != 6) {
            print_usage();
            return ERROR_INVALID_PARAMETR;
        }

        int flag_e = check_double_number(argv[2]);
        int flag_1 = check_double_number(argv[3]);
        int flag_2 = check_double_number(argv[4]);
        int flag_3 = check_double_number(argv[5]);

        if (!flag_e || !flag_1 || !flag_2 || !flag_3) {
            print_usage();
            return ERROR_INVALID_ARGUMENT;
        }

        char* endptr_e;
        char* endptr_1;
        char* endptr_2;
        char* endptr_3;

        double number_e = strtod(argv[2], &endptr_e);
        double number_1 = strtod(argv[3], &endptr_1);
        double number_2 = strtod(argv[4], &endptr_2);
        double number_3 = strtod(argv[5], &endptr_3);

        int answer = check_right_triangle(number_e, number_1, number_2, number_3);
        if (answer) {
            printf("Эти три числа являться сторонами прямоугольного треугольника\n");
        }
        else {
            printf("Эти три числа не являются сторонами прямоугольного треугольника\n");
        }

    }
    else {
        return ERROR_UNKNOWN_PARAMETR;
    }
    return SUCCESS;
}