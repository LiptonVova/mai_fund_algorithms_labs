#include "../include/solve.h"


void solve(int argc, char **argv) {
    if (argc != 3) {
        printf("-- Неправильный формат запуска программы\n");
        print_usage();
        return;
    }

    FILE* input_file = fopen(argv[1], "r");
    if (!input_file) {
        printf("-- Не удалось открыть файл %s\n", argv[1]);
        print_usage();
        return;
    }

    FILE* log_file = fopen(argv[2], "w");
    if (!log_file) {
        printf("-- Не удалось открыть файл %s\n", argv[2]);
        print_usage();
        fclose(input_file);
        return;
    }

    interpretator(input_file, log_file);    
}

void handle_type_operation(char *str, TypeOperation type_operation) {
    char str_expression[100] = "\0"; // правая часть равно (либо что в скобках команды print)
    switch (type_operation) {
        case (ASSIGNMENT):
            strcpy(str_expression, str + 2); // A=B 
            break;
        case (PRINT):
            strcpy(str_expression, str + 6); // PRINT(A)
            break;
        default:
            printf("-- Ошибка записи\n");
            break;
    }


    LinkedList_char output_queue = create_list_stack_queue();

    parse_expression(str_expression, &output_queue);

    printf("\n");
}

void interpretator(FILE* input_file, FILE* log_file) {
    // таблица переменных
    int table_variables[26];
    for (int i = 0; i < 26; ++i) table_variables[i] = INT_MIN;
    
    
    char str[100];
    while (!feof(input_file)) {
        fgets(str, sizeof(str), input_file);

        // удаляем пробелы из строки
        delete_spaces_and_upper_case(str);  

        // определяем тип операции
        TypeOperation type_operation; 
        define_type_operation(str, &type_operation);

        // в зависимости от типа операции меняется логика программы
        handle_type_operation(str, type_operation);        
    }
}