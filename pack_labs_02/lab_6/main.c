#include <stdio.h>
#include <stdlib.h>
#include "include/functions.h"
#include "include/print.h"
#include "include/handle.h"

int main(int argc, char *argv[]) {
    error_code_t error = SUCCESS;
    if ((error = validate_count_args(argc)) != SUCCESS) {
        return error;
    }

    FILE *input = fopen(argv[1], "r");
    if ((error = open_file(input)) != SUCCESS) {
        return error;
    }
    FILE *output = fopen(argv[2], "w");
    if ((error = open_file(output)) != SUCCESS) {
        return error;
    }

    int size_students = 0;

    Student **students = read_students_from_file(&error, input, &size_students);
    if (error != SUCCESS) {
        return error;
    }

    start_interactive_programm(&error, students, size_students, output);
    if (error != SUCCESS) {
        return error;
    }

    fclose(input);
    fclose(output);
    return 0;
}