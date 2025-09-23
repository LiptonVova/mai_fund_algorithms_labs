#include "../include/validate.h"
#include <string.h>


int validate_base(char * str) {
    int n = strlen(str);
    if (n > 2) {
        return 0;
    }
    for (int i = 0; i < n; ++i) {
        if (!(str[i] >= '0' && str[i] <= '9')) {
            return 0;
        }
    }
    return 1; 
}