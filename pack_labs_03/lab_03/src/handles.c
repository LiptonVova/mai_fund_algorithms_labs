#include "../include/handles.h"



void handle_print(FILE* output, LinkedList_Liver livers) {
    if (livers.size == 0) {
        fprintf(output, "Еще нет ни одного жителя!\n");
        fflush(output);
        return;
    }

    Node_Liver *node = livers.head;
    Liver liver = node->data;
    for (size_t i = 0; i < livers.size; ++i) {
        print_liver(output, liver);

        node = node->next;
        if (node) liver = node->data;
    }

}

void handle_search(LinkedList_Liver livers) {
    print_info_search();

    printf("Ваш выбор: ");
    int choice_search;
    scanf("%d", &choice_search); 

    if (choice_search < ID || choice_search > BREAK_SEARCH) {
        printf("Неизвестная команда\n");
        return;
    }

    switch (choice_search) {
        case ID:
            handle_search_id(livers);
            break;
        case SURNAME:
            handle_search_surname(livers);
            break;
        case NAME:
            handle_search_name(livers);
            break;
        case BIRTHDAY:
            handle_search_birthday(livers);
            break;
        case GENDER:
            handle_search_gender(livers);
            break;
        case BREAK_SEARCH:
            printf("Успешно отменено\n");
            break;
    }
}




void handle_edit(LinkedList_Liver *livers, LinkedList_Command *stack_commands) {
    printf("Добро пожаловать в меню редактирования жителей\n");
    printf("Для начала введите id жителя, которого вы хотите изменить\n");
    printf("id: ");

    int id = 0;
    scanf("%d", &id);

    Node_Liver *cur_node = livers->head;
    int index = 0; // номер по счету этого жителя
    while (cur_node != NULL && cur_node->data.id != id) {
        cur_node = cur_node->next;
        ++index;
    }
    if (!cur_node) {
        printf("Жителя с таким id нет в городе. Попробуйте еще раз...\n");
        return;
    }

    Command command;
    command.name_command = EDIT_LIVER;
    command.old_liver = copy_func(cur_node->data); // житель до изменений
    
    int choice = 0;
    do {
        print_liver(stdout, cur_node->data);
        printf("Выберите, что вы хотите изменить у этого жителя\n");
        print_info_edit();
        printf("Ваш выбор: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case (EDIT_SURNNAME):
            handle_edit_surname(cur_node);
            break;
            case (EDIT_NAME):
            handle_edit_name(cur_node);
            break;
            case (EDIT_MIDDLE_NAME):
            handle_edit_middle_name(cur_node);
            break;
            case (EDIT_DATE_BIRTHDAY):
            handle_edit_date_birthday(cur_node);
            break;
            case (EDIT_GENDER):
            handle_edit_gender(cur_node);
            break;
            case (EDIT_INCOME):
            handle_edit_income(cur_node);
            break;
            case (EXIT_EDIT):
            printf("Вы успешно вышли из меню редактирования жителя\n");
            break;
            default:
            printf("Неизвестная команда...\n");
        }
    }
    while (choice != EXIT_EDIT);
    
    // после изменения нужно поменять порядок (чтобы было отсортировано)
    Liver new_liver = copy_func(cur_node->data);
    
    command.new_liver = new_liver; // житель после изменений
    push_stack_Command(stack_commands, command);


    delete_at_list_Liver(livers, index); // удалили жителя
    insert_sort_livers(livers, new_liver); // добавили в отсортированный список
}

void handle_delete(LinkedList_Liver *livers, LinkedList_Command *stack_commands) {
    int id = -1;

    do {
        printf("Добро пожаловать в меню выселения (удаления) жителей!\n");
        printf("Для выхода вместо id напишите '-1'\n");
        printf("Введите id жителя, которого вы хотите удалить: ");
        scanf("%d", &id);

        if (id == -1) return;

        Node_Liver *cur_node = livers->head;
        size_t index = 0; // номер по счету этого жителя
        while (cur_node != NULL && cur_node->data.id != id) {
            cur_node = cur_node->next;
            ++index;
        }
        if (!cur_node) {
            printf("Жителя с таким id нет в городе. Попробуйте еще раз...\n");
            break;
        }
        
        Command command;
        command.name_command = DELETE_LIVER;
        command.old_liver = copy_func(cur_node->data); // житель до изменений
        command.new_liver = default_constructor(); // default liver
        push_stack_Command(stack_commands, command);

        delete_at_list_Liver(livers, index);
        printf("Житель успешно удален!\n");
    } while (id != -1);
}

void handle_add(LinkedList_Liver *livers, LinkedList_Command *stack_commands) {
    printf("Добро пожаловать в меню заселения (добавления) жителя\n");

    Liver new_liver;
    printf("Пожалуйста, введите id жителя: ");
    scanf("%ld", &new_liver.id);
    printf("Пожалуйста, введите фамилию жителя: ");
    char temp[100] = "\0";
    scanf("%s", temp);
    strcpy(new_liver.surname, temp);
    printf("Пожалуйста, введите имя жителя: ");
    scanf("%s", temp);
    strcpy(new_liver.name, temp);
    printf("Пожалуйста, введите отчество жителя (если нет, то введите '-'): ");
    scanf("%s", temp);
    strcpy(new_liver.middle_name, temp);
    printf("Пожалуйста, введите день рождения жителя (число от 1 до 31): ");
    scanf("%d", &new_liver.day_birthday);
    printf("Пожалуйста, введите месяц рождения жителя (число от 1 до 12): ");
    scanf("%d", &new_liver.month_birthday);
    printf("Пожалуйста, введите год рождения жителя: ");
    scanf("%d", &new_liver.year_birthday);
    printf("Пожалуйста, введите пол жителя (M - мужской, W - женский): ");
    char new_gender = ' ';
    scanf(" %c", &new_gender);
    new_gender = toupper(new_gender);
    new_liver.gender = new_gender;
    printf("Пожалуйста, введите средний доход жителя в месяц: ");
    scanf("%lf", &new_liver.average_income);

    Command command;
    command.name_command = ADD_LIVER;
    command.old_liver = default_constructor(); // default liver
    command.new_liver = copy_func(new_liver); // новый житель
    push_stack_Command(stack_commands, command);

    insert_sort_livers(livers, new_liver);
    printf("Житель успешно добавлен!\n");
}


void handle_choice(LinkedList_Liver *livers, LinkedList_Command *stack_commands, int choice, char * name_output_file, FILE* output_file) {
    switch (choice) {
        case DEFAULT:
            printf("Неизвестная ошибка\n");
            break;
        case SEARCH:
            handle_search(*livers);
            break;
        case EDIT:
            handle_edit(livers, stack_commands);
            break;
        case DELETE:
            handle_delete(livers, stack_commands);
            break;
        case ADD: 
            handle_add(livers, stack_commands);
            break;
        case SAVE_IN_FILE:
            // переоткрываю файл, чтобы стереть все данные с файла
            output_file = freopen(name_output_file, "w", output_file); 
            if (!output_file) {
                printf("Ошибка при открытии файла %s", name_output_file);
                break;
            }
            handle_print(output_file, *livers);
            break;
        case UNDO:
            handle_undo(livers, stack_commands);
            break;
        case PRINT:
            handle_print(stdout, *livers);
            break;
        case BREAK:
            printf("Будем рады, если навестите нас снова\n");
            printf("Программа завершается...\n");
            return; 
    }
}