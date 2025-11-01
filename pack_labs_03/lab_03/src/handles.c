#include "../include/handles.h"


void print_info_search() {
    printf("Выберите по какому параметру вы хотите сделать поиск:\n");
    printf("\t 1. Поиск по id\n");
    printf("\t 2. Поиск по фамилии\n");
    printf("\t 3. Поиск по имени\n");
    printf("\t 4. Поиск по дате рождения\n");
    printf("\t 5. Поиск по полу\n");
    printf("\t 6. Выйти из меню поиска\n");
}

void print_liver(Liver liver) {
    printf("- Житель №: %ld\n", liver.id);
    printf("\tФИО: %s %s %s\n", liver.surname, liver.name, liver.middle_name);
    printf("\tДата рождения: %02d.%02d.%d\n", liver.day_birthday, liver.month_birthday, liver.year_birthday);
    char gender_liver[64] = "\0";
    if (liver.gender == 'M' || liver.gender == 'm') strcpy(gender_liver, "Мужской");
    else if (liver.gender == 'W' || liver.gender == 'w') strcpy(gender_liver, "Женский");
    else strcpy(gender_liver, "Неизвестный пол");
    printf("\tПол: %s\n", gender_liver);
    printf("\tСреднемесячный доход: %lf\n", liver.average_income);
    printf("\n");

}

void handle_search_id(LinkedList livers) {
    printf("Найдем жителя по id!\n");
    printf("Введите желаемый id: ");
    int id = 0;
    scanf("%d", &id);

    Node *cur_node = livers.head;
    while (cur_node != NULL && cur_node->data.id != id) {
        cur_node = cur_node->next;
    }

    if (cur_node == NULL) {
        printf("Жителя с данным id не найдено\n");
        return;
    }
    print_liver(cur_node->data);
}

void handle_search_surname(LinkedList livers) {
    printf("Найдем житетей по фамилии!\n");
    printf("Введите желаемую фамилию: ");
    char surname[100] = "\0";
    scanf("%s", surname);

    Node *cur_node = livers.head;
    int flag = 0;
    while (cur_node != NULL) {
        if (strcmp(cur_node->data.surname, surname) == 0) {
            print_liver(cur_node->data);
            flag = 1;
        }
        cur_node = cur_node->next;
    }

    if (flag == 0) {
        printf("Жителей с данной фамилией в городе нет\n");
    }
}

void handle_search_name(LinkedList livers) {
    printf("Найдем житетей по имени!\n");
    printf("Введите желаемое имя: ");
    char name[100] = "\0";
    scanf("%s", name);

    Node *cur_node = livers.head;
    int flag = 0;
    while (cur_node != NULL) {
        if (strcmp(cur_node->data.name, name) == 0) {
            print_liver(cur_node->data);
            flag = 1;
        }
        cur_node = cur_node->next;
    }

    if (flag == 0) {
        printf("Жителей с данным именем в городе нет\n");
    }
}
void handle_search_birthday(LinkedList livers) {
    printf("Найдем житетей по дате рождения!\n");
    int day = 0, month = 0, year = 0;
    printf("Введите число: ");
    scanf("%d", &day);
    printf("Введите месяц: ");
    scanf("%d", &month);
    printf("Введите год: ");
    scanf("%d", &year);

    Node *cur_node = livers.head;
    int flag = 0;
    while (cur_node != NULL) {
        if (cur_node->data.day_birthday == day && cur_node->data.month_birthday == month && \
                cur_node->data.year_birthday == year) {
            print_liver(cur_node->data);
            flag = 1;
        }
        cur_node = cur_node->next;
    }

    if (flag == 0) {
        printf("Жителей с данной датой рождения в городе нет\n");
    }
}

void handle_search_gender(LinkedList livers) {
    printf("Найдем жителя по полу!\nВведите желаемый пол (Мужской-M, Женский-W): ");

    char gender;
    scanf(" %c", &gender);
    gender = toupper(gender);

    Node *cur_node = livers.head;
    int flag = 0;
    while (cur_node != NULL) {
        if (cur_node->data.gender == gender) {
            print_liver(cur_node->data);
            flag = 1;
        }
        cur_node = cur_node->next;
    }

    if (flag == 0) {
        printf("Жителей с данным именем в городе нет\n");
    }
}


void handle_search(LinkedList livers) {
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



void handle_print(LinkedList livers) {
    if (livers.size == 0) {
        printf("Еще нет ни одного жителя!\n");
        return;
    }

    Node *node = livers.head;
    Liver liver = node->data;
    for (size_t i = 0; i < livers.size; ++i) {
        print_liver(liver);

        node = node->next;
        if (node) liver = node->data;
    }
}

void print_info_edit() {
    printf("\t 1. фамилия\n");
    printf("\t 2. имя\n");
    printf("\t 3. отчество\n");
    printf("\t 4. дата рождения\n");
    printf("\t 5. пол\n");
    printf("\t 6. выйти из меню редактирования жителя\n");
}

void handle_edit_surname(Node* cur_node) {
    printf("Введите новую фамилию: ");
    char new_surname[100];
    scanf("%s", new_surname);

    strcpy(cur_node->data.surname, new_surname);

    printf("Успешно изменено!\n");
}
void handle_edit_name(Node* cur_node) {
    printf("Введите новое имя: ");
    char new_name[100];
    scanf("%s", new_name);

    strcpy(cur_node->data.name, new_name);

    printf("Успешно изменено!\n");
}
void handle_edit_middle_name(Node* cur_node) {
    printf("Введите новое отчество: ");
    char new_middle_name[100];
    scanf("%s", new_middle_name);

    strcpy(cur_node->data.middle_name, new_middle_name);

    printf("Успешно изменено!\n");
}
void handle_edit_date_birthday(Node* cur_node) {
    int new_day = 0, new_month = 0, new_year = 0;
    printf("Введите новое число рождения: ");
    scanf("%d", &new_day);
    printf("Введите новый месяц рождения (число от 1 до 12): ");
    scanf("%d", &new_month);
    printf("Введите новый год рождения: ");
    scanf("%d", &new_year);
    
    cur_node->data.day_birthday = new_day;
    cur_node->data.month_birthday = new_month;
    cur_node->data.year_birthday = new_year;

    printf("Успешно изменено!\n");
}
void handle_edit_gender(Node* cur_node) {
    printf("Введите новый пол (M - мужской, W - женский): ");
    char new_gender;
    scanf(" %c", &new_gender);
    new_gender = toupper(new_gender);

    cur_node->data.gender = new_gender;
}

void handle_edit(LinkedList *livers) {
    printf("Добро пожаловать в меню редактирования жителей\n");
    printf("Для начала введите id жителя, которого вы хотите изменить\n");
    printf("id: ");

    int id = 0;
    scanf("%d", &id);

    Node *cur_node = livers->head;
    while (cur_node != NULL && cur_node->data.id != id) {
        cur_node = cur_node->next;
    }
    if (!cur_node) {
        printf("Жителя с таким id нет в городе. Попробуйте еще раз...\n");
        return;
    }

    
    int choice = 0;
    do {
        print_liver(cur_node->data);
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
            case (EXIT_EDIT):
                printf("Вы успешно вышли из меню редактирования жителя\n");
                return;
            default:
                printf("Неизвестная команда...\n");
        }
    }
    while (choice != EXIT_EDIT);

    
}


void handle_choice(LinkedList livers, int choice) {
    switch (choice) {
        case DEFAULT:
            printf("Неизвестная ошибка\n");
            break;
        case SEARCH:
            handle_search(livers);
            break;
        case EDIT:
            handle_edit(&livers);
            break;
        case DELETE: 
            break;
        case ADD: 
            break;
        case SAVE_IN_FILE: 
            break;
        case UNDO:
            break;
        case PRINT:
            handle_print(livers);
            break;
        case BREAK:
            return; 
    }
}