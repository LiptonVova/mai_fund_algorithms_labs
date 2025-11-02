#include "../include/solve.h"


error_code_t solve() {
    printf("Введите название файла: ");
    char name_input_file[1000];
    scanf("%s", name_input_file);
    FILE * input_file = fopen(name_input_file, "r");
    if (!input_file) {
        printf("Ошибка открытия файла %s\nПожалуйста, введите существующий файл", name_input_file);
        return ERROR_OPEN_FILE;
    }
    else {
        printf("Файл успешно открыт!\n");
    }

    error_code_t error = SUCCESS;
    LinkedList_Liver livers = read_livers_from_file(input_file);

    start_interactive_programm(livers);

    fclose(input_file);
    return error;
}

void start_interactive_programm(LinkedList_Liver livers) {
    printf("Добро пожаловать в город Вовы Рыбина. Чувствуйте себя как дома!\n");

    printf("Перед началом проживания, пожалуйста, введите имя трассировочного файла, ");
    printf("для вывода данных о жителях города\n");

    char name_output_file[100];
    FILE *output_file = NULL;
    do {
        printf("Имя трассировочного файла: ");
        scanf("%s", name_output_file);

        output_file = fopen(name_output_file, "w");
        if (!output_file) {
            printf("Не удалось открыть файл.\n");
            printf("Перед продолжением, пожалуйста, введите валидный файл\n");
        }
    } 
    while (!output_file);

    printf("Файл успешно открыт. Спасибо за сотрудничество!\n");

    printf("--Идет создание стэка команд...\n");

    LinkedList_Command stack_commands = create_stack_command();

    printf("--Успешно создано!\n");

    // двусвязный список, который хранит что записали в файл
    // пока файл пустой, поэтому создаем пустой список
    LinkedList_Liver livers_in_file = create_list_Liver(delete_func, copy_func, comp, default_constructor);

    int choice = DEFAULT;
    while (choice != BREAK) {
        print_info();
        printf("Ваш выбор: ");
        scanf("%d", &choice);

        handle_choice(&livers, &stack_commands, choice, name_output_file, output_file, &livers_in_file);
    }

    fclose(output_file);
}

