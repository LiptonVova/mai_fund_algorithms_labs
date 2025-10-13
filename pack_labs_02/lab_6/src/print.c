#include "../include/print.h"


void print_usage() {
    printf("usage: ./main.out input_file output_file\n");
}

void print_greetings() {
    char greetings[] = "Добро пожаловать в интерактивную программу!!!\n\n";
    printf("%s", greetings);
}

void print_info() {
    char info[] = "Выберите, что вы хотите сделать:\n\
    1. Поиск по атрибуту\n\
    2. Сортировка по атрибуту\n\
    3. Вывести всех студентов\n\
    4. Вывести в трассировочный файл фамилии и имена студентов, чей средний балл\n\
        за все экзамены выше среднего балла за все экзамены по всем считанным из\n\
        файла студентам\n\
    5. Выход из программы\n";

    printf("%s", info);
}

void print_atributs() {
    char info[] = "Выберите, с каким атрибутом вы хотите выполнить операцию:\n\
    1. id\n\
    2. фамилия\n\
    3. имя\n\
    4. группа\n";

    printf("%s", info);
}

void print_student(FILE *stream, Student *student) {
    fprintf(stream, "Студент %u: фамилия: %s, имя: %s\n", student->id, student->surname, student->name);
    fprintf(stream, "           Группа: %s\n", student->group);
    unsigned int * marks = student->marks;
    fprintf(stream, "           Оценки: %u %u %u %u %u\n\n", marks[0], marks[1], marks[2], marks[3], marks[4]);
}

void print_all_students(Student **students, int size_students) {
    for (int i = 0; i < size_students; ++i) {
        print_student(stdout, students[i]);
    }
}

void print_student_average_point(FILE *stream, Student *student) {
    fprintf(stream, "Студент %u: фамилия: %s, имя: %s\n", student->id, student->surname, student->name);
    fprintf(stream, "           Группа: %s\n", student->group);
    double average_point = average_point_student(student);
    fprintf(stream,"           Средний балл за экзамены: %.2lf\n", average_point);
}