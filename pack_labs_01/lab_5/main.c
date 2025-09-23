#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/output.h"
#include "include/flags.h"
#include "include/dop_functions.h"

enum {
    SUCCESS,
    ERROR_FILE_OPEN,
    ERROR_COUNT_ARGUMENTS,
    ERROR_WRONG_FLAG,
    ERROR_MALLOC,
};


int main(int argc, char * argv[]) {
    if (argc <= 2) {
        printf("Неправильное количество аргументов\n\n");
        print_usage();
        return ERROR_COUNT_ARGUMENTS;
    }
    
    // входной файл
    char * filename_input = argv[1];
    FILE * file_input = fopen(filename_input, "r");
    if (!file_input) {
        printf("Ошибка при открытии файла %s\n", filename_input);
        return ERROR_FILE_OPEN;
    }


    char * array_flag = argv[2];
    if (array_flag[0] != '-' && array_flag[0] != '/') {
        printf("Неизвестный флаг\n");
        fclose(file_input);
        return ERROR_WRONG_FLAG;
    }
    
    
    // выходной файл  
    char * filename_output;
    if (array_flag[1] == 'n') {
        if (argc != 4) {
            printf("Введите имя выходного файла\n\n");
            print_usage();
            fclose(file_input);
            return ERROR_COUNT_ARGUMENTS;
        }
        filename_output = malloc(sizeof(char) * (strlen(argv[3]) + 1));
        filename_output[0] = '\0';
        strcat(filename_output, argv[3]);
    }
    else {
        int length = strlen(filename_input) + 5;
        filename_output = malloc(sizeof(char) * length);
        filename_output[0] = '\0';
        if (!filename_output) {
            printf("Ошибка при выделении памяти\n");
            fclose(file_input);
            return ERROR_MALLOC;
        }
        strcat(filename_output, "out_");
        strcat(filename_output, filename_input);
    }

    FILE * file_output = fopen(filename_output, "w");
    if (!file_output) {
        printf("Ошибка при открытии файла %s\n", filename_output);
        fclose(file_input);
        return ERROR_MALLOC;
    }


    // парсинг флага 
    char flag = ' ';

    if (strlen(array_flag) == 3) {
        if (array_flag[1] != 'n') {
            printf("Неизвестный флаг\n\n");
            print_usage();
            fclose(file_input);
            fclose(file_output);
            return ERROR_WRONG_FLAG;
        }
        flag = array_flag[2];
    }

    else if (strlen(array_flag) == 2) {
        if (argc > 3) {
            printf("Неправильное количество аргументов\n\n");
            print_usage();
            fclose(file_input);
            fclose(file_output);
            return ERROR_COUNT_ARGUMENTS;
        }
        flag = array_flag[1];
    }

    else {
        printf("Флаг должен состоять из одной буквы\n\n");
        print_usage();
        fclose(file_input);
        fclose(file_output);
        return ERROR_WRONG_FLAG;
    }

    // обработка флага
    if (flag == 'd') {
        d_flag(file_input, file_output);
    }
    else if (flag == 'i') {
        i_flag(file_input, file_output);
    }
    else if (flag == 's') {
        s_flag(file_input, file_output);
    }
    else if (flag == 'a') {
        a_flag(file_input, file_output);
    }

    else {
        printf("Неизвестный флаг\n\n");
        print_usage();
        fclose(file_input);
        fclose(file_output);
        return ERROR_WRONG_FLAG;
    }

    free(filename_output);

    fclose(file_input);
    fclose(file_output);
    return SUCCESS;
}