#ifndef READ_FROM_STREAM_H
#define READ_FROM_STREAM_H

#include <stdio.h>

typedef enum {
    SUCCESS,
    ERROR_ROMAN_NUMBER,
    ERROR_WRONG_LENGTH,
    ERROR_ZECKENDORF,
    ERROR_TRANSLATE_BASE_TO_TEN,
    ERROR_FORMAT,
} error_code_t;


void read_from_stream(error_code_t *error, FILE*stream, char* result, int* length, const int max_index, char last_char);
void read_from_buffer(error_code_t *error, const char** buffer, char* result, int* length, const int max_index, const char last_char);

#endif