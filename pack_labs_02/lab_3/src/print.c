#include "../include/print.h"


int overfprintf(FILE *stream, const char *format, ...) {
    va_list args;
    va_start(args, format);

    int written = 0;

    error_code_t error = SUCCESS;
    while (*format != '\0') {
        if (*format != '%') {
            fputc(*format, stream);
            written++;
            format++;
            continue;
        }   

        format++; // пропускаем %
        int specifier = parse_specifier(format);
        char result[1000];
        int written_cur = hanlde_specifier(&error, specifier, result, &format, args);
        written += written_cur;
        if (error != SUCCESS) {
            return error;
        }
        if (specifier == STANDART_SPECIFIER) {
            written += vfprintf(stream, result, args); // result в данном случае это строка, которая содержит спецификатор
        } 
        else {
            fprintf(stream, "%s", result); 
        }
    }

    return written;
}


int oversprintf(char *buffer, const char *format, ...) {
    va_list args;
    va_start(args, format);

    buffer[0] = '\0';

    int written = 0;

    error_code_t error = SUCCESS;
    while (*format != '\0') {
        if (*format != '%') {
            char temp_str[2];
            temp_str[0] = *format;
            temp_str[1] = '\0';
            strcat(buffer, temp_str);
            written++;
            format++;
            continue;
        }   

        format++; // пропускаем %
        int specifier = parse_specifier(format);
        char result[1000];
        int written_cur = hanlde_specifier(&error, specifier, result, &format, args);
        written += written_cur;
        if (error != SUCCESS) {
            return error;
        }
        if (specifier == STANDART_SPECIFIER) {
            char temp_buffer[1000];
            written += vsprintf(temp_buffer, result, args); // result в данном случае это строка, которая содержит спецификатор
            strcat(buffer, temp_buffer);
        } 
        else {
            char temp_buffer[1000];
            sprintf(temp_buffer, "%s", result); 
            strcat(buffer, temp_buffer);
        }
    }

    return written;
}