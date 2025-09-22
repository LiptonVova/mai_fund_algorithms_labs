#include "../include/validate.h"
#include <string.h>


int validate_double(char * str) {
    int index = 0;
    if (str[index] == '.') { // проверка что нет точки в начале
        return 0;
    }
    int n = strlen(str);
    if (str[index] == '0') { // проверка что число не ноль
        if (n > 1) {
            if (str[index + 1] != '.') {
                return 0;
            }
        } 
        else {
            return 0;    
        }
    }
    if (str[index] == '-') {
        return 0;
    }

    int flag_comma = 0;
    for (int i = index; i < n; ++i) {
        if (str[i] == '.' && flag_comma) {
            return 0;
        }
        else if (str[i] == '.') {
            flag_comma = 1;
            continue;
        }
        else if (str[i] >= '0' && str[i] <= '9') {
            continue;
        }
        return 0;
    }

    if (str[n - 1] == '.') { // проверка что нет точки в конце
        return 0;
    }
    return 1;
}