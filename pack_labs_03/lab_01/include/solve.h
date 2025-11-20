#ifndef SOLVE_H
#define SOLVE_H

#include <stdlib.h>
#include <string.h>

typedef enum {
    SUCCESS,
    ERROR_MALLOC,
} error_code_t ;

void translate_to_base(const int number, const int r, char *result);


#endif