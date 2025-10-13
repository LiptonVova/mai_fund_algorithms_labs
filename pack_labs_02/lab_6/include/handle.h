#ifndef HANDLE_H
#define HANDLE_H

#include "functions.h"
#include <stdbool.h>
#include "print.h"
#include <string.h>
#include "comp.h"

typedef enum {
    SEARCH = 1, 
    SORT = 2,
    PRINT_ALL = 3,
    MORE_AVERAGE_POINT = 4,
    STOP = 5,
} Choice;

typedef enum {
    ID = 1,
    SURNAME = 2,
    NAME = 3, 
    GROUP = 4,
} ChoiceAtributs;

void handle_choice(error_code_t *error, Student **students, int size_students, Choice choice, FILE*output);

void handle_search_id(Student **students, int size_students, FILE *output);
void handle_search_surname(Student **students, int size_students);
void handle_search_name(Student **students, int size_students);
void handle_search_group(Student **students, int size_students);

void handle_sort_id(Student **students, int size_students);
void handle_sort_surname(Student **students, int size_students);
void handle_sort_name(Student **students, int size_students);
void handle_sort_group(Student **students, int size_students);

void handle_more_average_point(Student **students, const int size_students, FILE *output);



#endif