#include "../include/handle.h"


void handle_choice(error_code_t *error, Student **students, int size_students, Choice choice, FILE *output) {
    if (choice == PRINT_ALL) {
        print_all_students(students, size_students);
        return;
    }
    else if (choice == MORE_AVERAGE_POINT) {
        handle_more_average_point(students, size_students, output);
        return;
    }
    print_atributs();
    int choice_atribut = 0;
    scanf("%d", &choice_atribut);
    if (choice_atribut < ID || choice_atribut > GROUP) {
        printf("Введите валидный выбор (Число от 1 до 4)\n");
        *error = ERROR_CHOICE;
        return;
    }
    if (choice == SEARCH) {
        if (choice_atribut == ID) handle_search_id(students, size_students, output);
        else if (choice_atribut == SURNAME) handle_search_surname(students, size_students);
        else if (choice_atribut == NAME) handle_search_name(students, size_students);
        else if (choice_atribut == GROUP) handle_search_group(students, size_students);
    }
    else if (choice == SORT) {
        if (choice_atribut == ID) handle_sort_id(students, size_students);
        else if (choice_atribut == SURNAME) handle_sort_surname(students, size_students);
        else if (choice_atribut == NAME) handle_sort_name(students, size_students);
        else if (choice_atribut == GROUP) handle_sort_group(students, size_students);
    }
}

void handle_search_id(Student **students, int size_students, FILE *output) {
    printf("Введите id, по которому надо выполнить поиск: ");
    unsigned int id = 0;
    bool flag = false;
    scanf("%u", &id);

    printf("Хотите ли записать студента/студентов с найденным id в трассировочный файл? (y/n) ");
    char answer = '\0';
    scanf("%c", &answer);
    while (answer != 'y' && answer != 'n') {
        scanf("%c", &answer);
    }
    bool write = false;
    if (answer == 'y') write = true;

    if (write) {
        fprintf(output, "Результат поиска студента/студентов с id %u:\n", id);
    }

    for (int i = 0; i < size_students; ++i) {
        if (students[i]->id == id) {

            Student* student = students[i];
            print_student(stdout, student);
            flag = true;
            if (write) {
                print_student_average_point(output, student);
            }
        }
    }
    if (!flag) {
        printf("Студента с id %u не найдено\n\n", id);
        if (write) {
            fprintf(output, "Студента с id %u не найдено\n\n", id);
        }
    }
}

void handle_search_surname(Student **students, int size_students) {
    printf("Введите фамилию, по которой надо выполнить поиск: ");
    char surname[100];
    bool flag = false;
    scanf("%s", surname);
    for (int i = 0; i < size_students; ++i) {
        if (strcmp(students[i]->surname, surname) == 0) {
            Student* student = students[i];
            print_student(stdout, student);
            flag = true;
        }
    }
    if (!flag) {
        printf("Студента с фамилией %s не найдено\n\n", surname);
    }
}

void handle_search_name(Student **students, int size_students) {
    printf("Введите имя, по которому надо выполнить поиск: ");
    char name[100];
    bool flag = false;
    scanf("%s", name);
    for (int i = 0; i < size_students; ++i) {
        if (strcmp(students[i]->name, name) == 0) {
            Student* student = students[i];
            print_student(stdout, student);
            flag = true;
        }
    }
    if (!flag) {
        printf("Студента с именем %s не найдено\n\n", name);
    }
}

void handle_search_group(Student **students, int size_students) {
    printf("Введите группу, по которой надо выполнить поиск: ");
    char group[100];
    bool flag = false;
    scanf("%s", group);
    for (int i = 0; i < size_students; ++i) {
        if (strcmp(students[i]->group, group) == 0) {
            Student* student = students[i];
            print_student(stdout, student);
            flag = true;
        }
    }
    if (!flag) {
        printf("Студентов с групой %s не найдено\n\n", group);
    }
}

void handle_sort_id(Student **students, int size_students) {
    qsort(students, size_students, sizeof(Student*), comp_id);
    printf("Успешно отсортировано по id\n\n");
}

void handle_sort_surname(Student **students, int size_students) {
    qsort(students, size_students, sizeof(Student*), comp_surname);
    printf("Успешно отсортировано по фамилии\n\n");
}

void handle_sort_name(Student **students, int size_students) {
    qsort(students, size_students, sizeof(Student*), comp_name);
    printf("Успешно отсортировано по имени\n\n");
}

void handle_sort_group(Student **students, int size_students) {
    qsort(students, size_students, sizeof(Student*), comp_group);
    printf("Успешно отсортировано по группе\n\n");
}


void handle_more_average_point(Student **students, const int size_students, FILE *output) {
    double average_point = average_point_students(students, size_students);
    fprintf(output, "Результаты поиска студентов, чей средний бапл выше, чем общий средний балл за все экзамены:\n");
    for (int i = 0; i < size_students; ++i) {
        double average_point_cur_student = average_point_student(students[i]);
        if (average_point_cur_student > average_point) {
            print_student_average_point(output, students[i]);
        }
    }
    printf("Успешно выполнено!\n\n");
}