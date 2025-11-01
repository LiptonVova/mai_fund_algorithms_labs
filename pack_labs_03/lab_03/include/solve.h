#ifndef SOLVE_H
#define SOLVE_H


#include <stdio.h>
#include <string.h>
#include "handles.h"

typedef enum {
    SUCCESS, 
    ERROR_OPEN_FILE,
    ERROR_MALLOC,
} error_code_t;


error_code_t solve();
LinkedList read_livers_from_file(error_code_t *error, FILE* input);
void insert_sort_livers(LinkedList *livers, Liver liver);

void start_interactive_programm(LinkedList livers);
void print_info();

#endif