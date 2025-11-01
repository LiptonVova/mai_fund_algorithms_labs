#ifndef HANDLES_H
#define HANDLES_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "linkedList.h"


typedef struct {
    size_t id;
    char surname[100];
    char name[100];
    char middle_name[100];
    int day_birthday;
    int month_birthday;
    int year_birthday;
    char gender;
    double average_income;
} Liver ;

// двусвязный список жителей
DEFINE_LIST_STACK(Liver)


typedef enum {
    DEFAULT = 0,
    SEARCH = 1,
    EDIT = 2,
    DELETE = 3,
    ADD = 4,
    SAVE_IN_FILE = 5,
    UNDO = 6,
    PRINT = 7,
    BREAK = 8,
} Choices;

typedef enum {
    ID = 1,
    SURNAME = 2,
    NAME = 3,
    BIRTHDAY = 4,
    GENDER = 5,
    BREAK_SEARCH = 6,
} ChoicesSearch;


typedef enum {
    EDIT_SURNNAME = 1,
    EDIT_NAME = 2,
    EDIT_MIDDLE_NAME = 3,
    EDIT_DATE_BIRTHDAY = 4,
    EDIT_GENDER = 5, 
    EXIT_EDIT = 6
} ChoicesEdit;

void handle_choice(LinkedList livers, int choice);



#endif