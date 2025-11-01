#include "../include/solve.h"

void delete_func(Liver liver) {
}

Liver copy_func(Liver other) {
    Liver cur;
    cur.id = other.id;
    strcpy(cur.surname, other.surname);
    strcpy(cur.name, other.name);
    strcpy(cur.middle_name, other.middle_name);
    cur.day_birthday = other.day_birthday;
    cur.month_birthday = other.month_birthday;
    cur.year_birthday = other.year_birthday;
    cur.gender = other.gender;
    cur.average_income = other.average_income;
    return cur;
}

int comp(Liver liver_1, Liver liver_2) {
    int comp_id_name = liver_1.id == liver_2.id && strcmp(liver_1.surname, liver_2.surname) && \
                    strcmp(liver_1.name, liver_2.name) &&  strcmp(liver_1.middle_name, liver_2.middle_name);
    int comp_birthday = liver_1.day_birthday == liver_2.day_birthday && liver_1.month_birthday == liver_2.month_birthday && \
                    liver_1.year_birthday == liver_2.year_birthday;
    int comp_gender_income = liver_1.gender == liver_2.gender && liver_1.average_income == liver_2.average_income;
    return comp_id_name && comp_birthday && comp_gender_income;
}

Liver default_constructor() {
    Liver liver;
    liver.id = 0;
    strcpy(liver.surname,"\0");
    strcpy(liver.name, "\0");
    strcpy(liver.middle_name, "\0");
    liver.day_birthday = 0;
    liver.month_birthday = 0;
    liver.year_birthday = 0;
    liver.gender = 'M';
    liver.average_income = 0;
    return liver;
}

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
    LinkedList livers = read_livers_from_file(&error, input_file);

    start_interactive_programm(livers);

    return error;
}

LinkedList read_livers_from_file(error_code_t *error, FILE* input) {
    LinkedList livers = create_list(delete_func, copy_func, comp, default_constructor);
    while (!feof(input)) {
        Liver liver;

        fscanf(input, "%ld %s %s",&liver.id, liver.surname, liver.name);
        char temp[100] = "\0";
        fscanf(input, "%s", temp);
        char *end_ptr;
        int num = strtol(temp, &end_ptr, 10);
        if (*end_ptr != '\0') {
            // значит это было отчество
            strcpy(liver.middle_name, temp);
            // чтобы было одинаковое колво считанных полей, надо считать еще дату рождения
            fscanf(input, "%d", &liver.day_birthday);
        } 
        else {
            // значит уже началась дата рождения
            strcpy(liver.middle_name, "-");
            liver.day_birthday = num; 
        }
        fscanf(input, "%d %d %c %lf\n", &liver.month_birthday, &liver.year_birthday, \
            &liver.gender, &liver.average_income);

        
        insert_sort_livers(&livers, liver);        
    }

    return livers;
}

int compare_by_birthdate(const Liver a, const Liver b) {
    if (a.year_birthday != b.year_birthday)
        return a.year_birthday - b.year_birthday;
    if (a.month_birthday != b.month_birthday)
        return a.month_birthday - b.month_birthday;
    return a.day_birthday - b.day_birthday;
}


void insert_sort_livers(LinkedList *livers, Liver liver) {
    size_t i = 0;

    Node *current = livers->head;
    
    while (current != NULL && compare_by_birthdate(current->data, liver) < 0) {
        current = current->next;
        i++;
    }    

    insert_at_list(livers, i, liver);
}

void start_interactive_programm(LinkedList livers) {
    printf("Добро пожаловать в город Вовы Рыбина. Чувствуйте себя как дома!\n");

    printf("Перед началом проживания, пожалуйста, введите имя трассировочного файла, ");
    printf("для вывода данных о жителях города\n");

    FILE *output_file = NULL;
    do {
        printf("Имя трассировочного файла: ");
        char name_output_file[100];
        scanf("%s", name_output_file);

        output_file = fopen(name_output_file, "w");
        if (!output_file) {
            printf("Не удалось открыть файл.\n");
            printf("Перед продолжением, пожалуйста, введите валидный файл\n");
        }
    } 
    while (!output_file);

    printf("Файл успешно открыт. Спасибо за сотрудничество!\n");

    int choice = DEFAULT;
    while (choice != BREAK) {
        print_info();
        printf("Ваш выбор: ");
        scanf("%d", &choice);

        handle_choice(livers, choice);

    }


}

void print_info() {
    printf("Пожалуйста, введите номер команды, которую вы хотите исполнить:\n");
    printf("\t1. Найти жителя по параметрам\n");
    printf("\t2. Отредактировать жителя\n");
    printf("\t3. Выселить жителя из города (удалить)\n");
    printf("\t4. Заселить жителя в город (добавить)\n");
    printf("\t5. Сохранить информацию о жителях города в файл\n");
    printf("\t6. Отменить последние N/2 команд\n");
    printf("\t7. Вывести всех жителей города\n");
    printf("\t8. Уехать из города (завершить выполнение программы)\n");
}