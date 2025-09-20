#include "../include/str_to_int.h"


int str_to_int(char * number) {
    int res = 0;
    char *p = number;

    int flag = 1;

    if (*p == '-') {
        flag *= -1;
        p++;
    }

    while (*p != 0) {
        res = res * 10 + (*p - '0');
        p++;
    }

    return res * flag;
}