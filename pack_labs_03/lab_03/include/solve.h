#ifndef SOLVE_H
#define SOLVE_H


#include <stdio.h>
#include <string.h>
#include "handles.h"
#include "config.h"
#include "utils.h"
#include "undo.h"

typedef enum {
    SUCCESS, 
    ERROR_OPEN_FILE,
    ERROR_MALLOC,
} error_code_t;


error_code_t solve();

void start_interactive_programm(LinkedList_Liver livers);

#endif