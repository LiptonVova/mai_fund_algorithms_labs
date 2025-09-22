#include <stdio.h>
#include "include/output.h"
#include "include/solve.h"


enum {
    SUCCESS,
    ERROR_WRONG_COUNT_ARGUMENTS,
    ERROR_FILE_OPEN,
    ERROR_DURING_WORK,
};


int main(int argc, char * argv[]) {
    if (argc != 3) {
        print_usage();
        return ERROR_WRONG_COUNT_ARGUMENTS;
    }

    FILE * input = fopen(argv[1], "r");

    if (!input) {
        printf("Ошибка при открытии файла %s\n\n", argv[1]);
        print_usage();
        return ERROR_FILE_OPEN;
    }

    FILE * output = fopen(argv[2], "w");

    if (!output) {
        printf("Ошибка при открытии файла %s\n\n", argv[2]);
        print_usage();
        fclose(input);
        return ERROR_FILE_OPEN;
    }

    int flag = solve(input, output);
    if (flag == -1) {
        printf("Возникла ошибка при работе программы\n");
        fclose(input);
        fclose(output);
        return ERROR_DURING_WORK;
    }
    printf("Программа успешно выполнена. Результат в файле %s\n", argv[2]);

    fclose(input);
    fclose(output);
    return SUCCESS;
}