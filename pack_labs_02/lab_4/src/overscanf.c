#include "../include/overscanf.h"

int overfscanf(FILE *stream, const char *format, ...) {
    va_list args;
    va_start(args, format);

    int count = 0;
    char c;
    int specifier = 0;
    error_code_t error = SUCCESS;
    while (*format) {
        if (*format == '%') {
            format++; // пропускаем %
            specifier = parse_specifier(format);
            if (specifier >= STANDART_SPECIFIER) {
                int buf_size = 1000;
                char buffer[buf_size];
                char char_specifier = '\0'; // для стандартного спецификатора
                if (specifier == STANDART_SPECIFIER) {
                    char_specifier = *format; // стандартный спецификатор 
                    format += 1; // проходим через спецификатор
                }
                else {
                    format += 2; // проходим через спецификатор
                }
                char last_char = *format;  // получаем символ, после которого надо закончить 
                int length = 0;
                read_from_stream(&error, stream, buffer, &length, buf_size - 1, last_char);
                if (error != SUCCESS) {
                    break;
                }
                handle_specifier(&error, buffer, args, specifier, char_specifier);
                if (error != SUCCESS) {
                    break;
                }
                count++;
            }
            else if (specifier == NOT_SPECIFIER) {
                c = fgetc(stream);
                if (c != *format) {
                    break;
                }
            }
        }
        
        else {
            c = fgetc(stream);
            if (c != *format) {
                break;
            }
        }
        if (*format) {
            format++;
        }
    }


    if (count == 0) {
        return EOF;
    }
    return count;
}

int oversscanf(const char *buffer, const char *format, ...) {
    va_list args;
    va_start(args, format);

    int count = 0;
    char c;
    int specifier = 0;
    error_code_t error = SUCCESS;
    while (*format) {
        if (*format == '%') {
            format++; // пропускаем %
            specifier = parse_specifier(format);
            if (specifier >= STANDART_SPECIFIER) {
                int buf_size = 1000;
                char buffer_number[buf_size];
                char char_specifier = '\0'; // для стандартного спецификатора
                if (specifier == STANDART_SPECIFIER) {
                    char_specifier = *format; // стандартный спецификатор 
                    format += 1; // проходим через спецификатор
                }
                else {
                    format += 2; // проходим через спецификатор
                }
                char last_char = *format; // получаем символ, после которого надо закончить 
                int length = 0;
                read_from_buffer(&error, &buffer, buffer_number, &length, buf_size - 1, last_char);
                if (error != SUCCESS) {
                    break;
                }
                handle_specifier(&error, buffer_number, args, specifier, char_specifier);
                if (error != SUCCESS) {
                    break;
                }
                count++;
            }
            else if (specifier == NOT_SPECIFIER) {
                c = *buffer;
                if (c != *format) {
                    break;
                }
                buffer++;
            }
        }
        else {
            c = *buffer;
            buffer++;
            if (c != *format) {
                break;
            }
        }
        if (*format) {
            format++;
        }
    }


    if (count == 0) {
        return 0;
    }
    return count;
}