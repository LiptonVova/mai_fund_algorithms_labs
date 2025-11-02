#ifndef HANDLES_H
#define HANDLES_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>

// полезные функции
#include "utils.h"

// заголовочные файлы для конкретной команды
#include "search.h"
#include "edit.h"

// заголовочные файлы для структур 
#include "config.h"
#include "undo.h"

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
    EDIT_INCOME = 6,
    EXIT_EDIT = 7
} ChoicesEdit;

void handle_choice(LinkedList_Liver *livers, LinkedList_Command *stack_commands, int choice, char * name_output_file, FILE* output_file);

#endif