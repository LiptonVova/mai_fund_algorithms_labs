#ifndef FUNCTIONS_H
#define FUNCTIONS_H


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct {
    unsigned int id;
    char * name;
    char * surname;
    char * group;
    unsigned int * marks;
} Student;

typedef enum {
    SUCCESS,
    ERORR_WRONG_ARGUMENTS,
    ERROR_OPEN_FILE,
    ERROR_MALLOC, 
    ERROR_CHOICE,
} error_code_t;




void print_usage();
int open_file(FILE *file);
int validate_count_args(int argc);

Student** read_students_from_file(error_code_t *error, FILE *input, int *length);

double average_point_student(Student *student);
double average_point_students(Student **students, const int size_students);

void start_interactive_programm(error_code_t *error, Student **students, int size_students, FILE*output);

#endif