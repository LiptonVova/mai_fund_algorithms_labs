#include "../include/functions.h"

#include "../include/print.h"
#include "../include/handle.h"



int validate_count_args(int argc) {
    if (argc != 3) {
        printf("Неправильное колво аргументов\n");
        print_usage();
        return ERORR_WRONG_ARGUMENTS;
    }
    return SUCCESS;
}

int open_file(FILE *file) {
    if (!file) {
        printf("Ошибка при открытии файла\n");
        print_usage();
        return ERROR_OPEN_FILE;
    }
    return SUCCESS;
}


bool check_memory_alloc(error_code_t *error, void*memory, char* name) {
    if (!memory) {
        printf("Ошибка при выделении памяти для %s\n", name);
        *error = ERROR_MALLOC;
        return false;
    }
    return true;
}

Student* read_students_from_file_impl(error_code_t *error, FILE *input) {
    unsigned int id = 0;
    char* name = (char*)malloc(sizeof(char*)*100);
    char* surname = (char*)malloc(sizeof(char*)*100);
    char* group = (char*)malloc(sizeof(char*)*100);
    
    if (!check_memory_alloc(error, name, "Name") || !check_memory_alloc(error, surname, "Surname") || !check_memory_alloc(error, group, "Group")) {
        return NULL;
    }
    unsigned int * marks = (unsigned int*)malloc(sizeof(unsigned int) * 5);
    if (!check_memory_alloc(error, marks, "Marks")) {
        return NULL;
    }
    fscanf(input, "%d %s %s %s %u %u %u %u %u\n", &id, name, surname, group, &marks[0], &marks[1], &marks[2], &marks[3], &marks[4]);

    Student *cur_student = (Student*)malloc(sizeof(Student));
    if (!check_memory_alloc(error, cur_student, "Student")) {
        return NULL;
    }
    cur_student->id = id;
    cur_student->name = name;
    cur_student->surname = surname;
    cur_student->group = group;
    cur_student->marks = marks; 

    return cur_student;
}


Student** read_students_from_file(error_code_t *error, FILE *input, int *length) {
    int buf_size = 10;
    Student **students = (Student**)malloc(sizeof(Student*) * buf_size);

    int index_student = 0;
    if (!students) {
        printf("Ошибка при выделении памяти под массив students\n");
        *error = ERROR_MALLOC;
        return NULL;
    }

    while (!feof(input)) {
        Student * cur_student = read_students_from_file_impl(error, input);

        if (index_student >= buf_size) {
            buf_size *= 2;
            Student **tmp = (Student**)realloc(students, sizeof(Student*) * buf_size);
            if (!check_memory_alloc(error, tmp, "Students")) {
                return NULL;
            }
            students = tmp;            
        }
        students[index_student] = cur_student;
        index_student++;
    }
    *length = index_student;
    return students;
}

double average_point_student(Student *student) {
    double average_point = 0.0;
    for (int i = 0; i < 5; ++i) {
        average_point += student->marks[i];
    }
    average_point /= 5.0;
    return average_point;
}

double average_point_students(Student **students, const int size_students) {
    double summ = 0;

    for (int i = 0; i < size_students; ++i) {
        summ += average_point_student(students[i]);
    }

    return summ/size_students;
}


void start_interactive_programm(error_code_t *error, Student **students, int size_students, FILE*output) {
    print_greetings();
    print_info();

    int choice = 0;
    scanf("%d", &choice);
    if (choice < SEARCH || choice > STOP) {
        printf("Введите валидный выбор (Число от 1 до 5)\n");
        *error = ERROR_CHOICE;
        return;
    } 
    while (choice != STOP) {


        handle_choice(error, students, size_students, choice, output);
        if (*error != SUCCESS) {
            return;
        }
        print_info();
        scanf("%d", &choice);
    }


    for (int i = 0; i < size_students; ++i) {
        free(students[i]->marks);
    }
    free(students); 
}