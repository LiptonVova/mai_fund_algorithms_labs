#ifndef PRINT_H
#define PRINT_H

#include <stdio.h>
#include "functions.h"

void print_usage();
void print_greetings();
void print_info();
void print_atributs();
void print_student(FILE *stream, Student *student);
void print_all_students(Student **students, int size_students);
void print_student_average_point(FILE *stream, Student *student);

#endif