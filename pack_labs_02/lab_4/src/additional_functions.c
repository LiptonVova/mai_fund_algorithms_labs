#include "../include/additional_functions.h"


void read_from_stream(error_code_t *error, FILE*stream, char* result, int* length, const int max_index, char last_char) {
    if (last_char == '\0') {
        last_char = EOF;
    }
    int index = 0;
    char c = fgetc(stream);
    while (c != EOF && c != '\0' && c != last_char) {
        result[index] = c;
        c = fgetc(stream);
        index++;
        if (index == max_index) {
            *error = ERROR_WRONG_LENGTH;
            return;
        }
    }   
    if (c != last_char) { // то тогда format не соответствует файлу 
        *error = ERROR_FORMAT;
        return;
    }
    result[index] = '\0';
    *length = index;
}

void read_from_buffer(error_code_t *error, const char** buffer, char* result, int* length, const int max_index, const char last_char) {
    int index = 0;
    char c = **buffer;
    (*buffer)++;
    while (c != '\0' && c != last_char) {
        result[index] = c;
        c = **buffer;
        index++;
        if (index == max_index) {
            *error = ERROR_WRONG_LENGTH;
            return;
        }
        (*buffer)++;
    }
    if (c != last_char) {
        *error = ERROR_FORMAT;
        return;
    }
    result[index] = '\0';
    *length = index;
}