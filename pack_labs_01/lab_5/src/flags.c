#include "../include/flags.h"
#include "../include/dop_functions.h"


void d_flag(FILE* file_input, FILE* file_output) {
    char c;
    while ( (c = fgetc(file_input)) != EOF) {
        if (c <= '9' && c >= '0') {
            continue;
        }
        fputc(c, file_output);
    }
}

void i_flag(FILE* file_input, FILE* file_output) {
    int result = 0;
    char c = fgetc(file_input);
    while (c != EOF) {
        if (c == '\n') {
            fprintf(file_output, "%d\n", result);
            result = 0;
        }

        if ( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            ++result;
        }
        c = fgetc(file_input);
    }
    fprintf(file_output, "%d\n", result);
    
}

void s_flag(FILE* file_input, FILE* file_output) {
    int result = 0;
    char c = fgetc(file_input);
    while (c != EOF) {
        if (c == '\n') {
            fprintf(file_output, "%d\n", result);
            result = 0;
            c = fgetc(file_input);
            continue;
        }

        if ( !( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == ' ') ) {
            ++result;
        }

        c = fgetc(file_input);
    }

    fprintf(file_output, "%d\n", result);
}

void a_flag(FILE* file_input, FILE* file_output) { 
    char c = fgetc(file_input);
    char result[34];
    int ascii_code = ' '; 
    int index = 0;
    int i = 0;
    while (c != EOF) {
        if (! (c >= '0' && c <= '9') && c != '\n' && c != ' ') {
            ascii_code = c; 
            index = ten_to_hex(result, ascii_code);
            for (i = index; i < 33; ++i) {
                fputc(result[i], file_output);
            }            
        }
        else {
            fputc(c, file_output);
        }
        c = fgetc(file_input);
    }
}

