#include "../include/check.h"



int check_double_number(char * str) {
    char * ptr = str;

    if (*ptr == '-') {
        ptr++;
        if (*ptr == 0) {
            return 0;
        }
    } 

    if (*ptr == '.') { // если первый элемент точка
        return 0;
    }

    int flag_comma = 0;
    while (*ptr != 0) {
        if (*ptr == '.') {
            if (flag_comma) {
                return 0;
            }
            flag_comma = 1;
        }

        if ( !(*ptr >= '0' && *ptr <= '9') && *ptr != '.') {
            return 0;
        }
        ptr++;
    }

    if (*(--ptr) == '.') { // если последний элемент точка
        return 0; 
    }

    return 1; 
}


int check_int_number(char * str) {
    char * ptr = str;

    if (*ptr == '-') {
        ptr++;
        if (*ptr == 0) {
            return 0;
        }
    }

    int length = 0;
    while (*ptr != 0) {
        if (! (*ptr >= '0' && *ptr <= '9')) {
            return 0;
        }
        length++;
        ptr++;
    }
    return length <= 9;
}

