#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <string.h>

typedef enum {
    SUCCESS,
    ERROR_OPEN_FILE = -1,
} error_code_t ;

int open_file(char* message, char* type, char *filename, FILE **file);


#endif