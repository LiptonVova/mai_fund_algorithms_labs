#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "include/str_to_int.h"
#include "include/main_functions.h"


typedef enum {
    ERROR_WRONG_COUNT_ARGUMENTS,
    ERROR_MALLOC,  
    ERROR_NOT_NUMBER,
    ERROR_WRONG_ARGUMENT,
} STATUS_CODES;


int main(int argc, char * argv[]) {
    if (argc != 3) {
        printf("Неправильное количество аргументов\n\n");
        print_usage();
        return ERROR_WRONG_COUNT_ARGUMENTS;
    }

    char* p = argv[1];
    if (*p == '-') {
        p++;
    }
    while ( *p != 0 ) {
        if ( *p >= '0' && *p <= '9') {
            p++;
            continue;
        }
        printf("Введите число в десятичной системе счисления\n\n");
        print_usage();
        return ERROR_NOT_NUMBER;
    } 

    const int number = str_to_int(argv[1]);

    if (strcmp(argv[2], "-h") == 0 || strcmp(argv[2], "/h") == 0) {
        int * result = malloc(sizeof(int) * 100);
        if (!result) {
            printf("Ошибка при выделении памяти\n");
            return ERROR_MALLOC;
        }
        int index = h_flag(result, number);
        if (index == 0) {
            printf("Таких чисел нет");
        }
        else {
            for (int i = 0; i < index; ++i) {
                printf("%d ", result[i]);
            }
        }
        printf("\n");
        free(result);
    }
    
    else if (strcmp(argv[2], "-p") == 0 || strcmp(argv[2], "/p") == 0) {
        int res = p_flag(number);
        if (res) {
            printf("%d - простое\n", number);
        } 
        else {
            printf("%d - составное\n", number);
        }
    }

    else if (strcmp(argv[2], "-s") == 0 || strcmp(argv[2], "/s") == 0) {
        char * result = malloc(sizeof(char) * 34);
        if (!result) {
            printf("Ошибка при выделении памяти\n");
            return ERROR_MALLOC;
        }
        int index;
        if (number < 0) {
            index = s_flag(result, -number); 
            printf("-");
        }
        else {
            index = s_flag(result, number);
        }

        for (int i = index; i < 33; ++i) {
            printf("%c ", result[i]);
        }
        printf("\n");
        free(result);
    }

    else if (strcmp(argv[2], "-e") == 0 || strcmp(argv[2], "/e") == 0) {
        if (number > 10) {
            printf("Введите число, не превосходящее 10\n\n");
            print_usage();
            return ERROR_WRONG_ARGUMENT;
        }
        if (number < 1) {
            printf("Введите число большее 1\n\n");
            print_usage();
            return ERROR_WRONG_ARGUMENT;
        }
 
        long long ** result = malloc(sizeof(long long*) * 10);
        for (int i = 0; i < 10; ++i) {
            result[i] = malloc(sizeof(long long) * number);
            if (!result[i]) {
                printf("Ошибка при выделении памяти\n");
                return ERROR_MALLOC;
            }
        }
        e_flag(result, number);

        printf(" ");
        for (int i = 1; i <= number; ++i) {
            printf("%12d ", i);
        }
        printf("\n");
        for (int i = 0; i < 10; ++i) {
            printf("%d", i + 1);
            for (int j = 0; j < number; ++j) {
                printf("%12lld ", result[i][j]);
            }
            printf("\n");
        }

        for (int i = 0; i < 10; ++i) {
            free(result[i]);
        }
        free(result);  
    }

    else if (strcmp(argv[2], "-a") == 0 || strcmp(argv[2], "/a") == 0) {
        printf("%lld\n", a_flag(number));
    }

    else if (strcmp(argv[2], "-f") == 0 || strcmp(argv[2], "/f") == 0) {   
        if (number < 0) {
            printf("ВВедите неотрицательное число\n\n");
            print_usage();
            return ERROR_WRONG_ARGUMENT;
        }
        printf("%lld\n", f_flag(number));
    }
    else {
        printf("Неизвестный флаг\n\n");
        print_usage();
    }

    return 0;
}       