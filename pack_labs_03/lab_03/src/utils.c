#include "../include/utils.h"


int compare_by_birthdate(const Liver a, const Liver b) {
    if (a.year_birthday != b.year_birthday)
        return a.year_birthday - b.year_birthday;
    if (a.month_birthday != b.month_birthday)
        return a.month_birthday - b.month_birthday;
    return a.day_birthday - b.day_birthday;
}


void insert_sort_livers(LinkedList_Liver *livers, Liver liver) {
    size_t i = 0;

    Node_Liver *current = livers->head;
    
    while (current != NULL && compare_by_birthdate(current->data, liver) < 0) {
        current = current->next;
        i++;
    }    

    insert_at_list_Liver(livers, i, liver);
}

LinkedList_Liver read_livers_from_file(FILE* input) {
    LinkedList_Liver livers = create_list_Liver(delete_func, copy_func, comp, default_constructor);
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


// функции вывода любой информации в терминал  
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

void print_info_search() {
    printf("Выберите по какому параметру вы хотите сделать поиск:\n");
    printf("\t 1. Поиск по id\n");
    printf("\t 2. Поиск по фамилии\n");
    printf("\t 3. Поиск по имени\n");
    printf("\t 4. Поиск по дате рождения\n");
    printf("\t 5. Поиск по полу\n");
    printf("\t 6. Выйти из меню поиска\n");
}

void print_liver(FILE * output, const Liver liver) {
    fprintf(output, "- Житель №: %ld\n", liver.id);
    fprintf(output, "\tФИО: %s %s %s\n", liver.surname, liver.name, liver.middle_name);
    fprintf(output, "\tДата рождения: %02d.%02d.%d\n", liver.day_birthday, liver.month_birthday, liver.year_birthday);
    char gender_liver[64] = "\0";
    if (liver.gender == 'M' || liver.gender == 'm') strcpy(gender_liver, "Мужской");
    else if (liver.gender == 'W' || liver.gender == 'w') strcpy(gender_liver, "Женский");
    else strcpy(gender_liver, "Неизвестный пол");
    fprintf(output, "\tПол: %s\n", gender_liver);
    fprintf(output, "\tСреднемесячный доход: %lf\n", liver.average_income);
    fprintf(output, "\n");
    fflush(output);

}

void print_info_edit() {
    printf("\t 1. фамилия\n");
    printf("\t 2. имя\n");
    printf("\t 3. отчество\n");
    printf("\t 4. дата рождения\n");
    printf("\t 5. пол\n");
    printf("\t 6. среднемесячный доход\n");
    printf("\t 7. выйти из меню редактирования жителя\n");
}