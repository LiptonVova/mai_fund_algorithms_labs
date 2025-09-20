#include "../include/dop_functions.h"
#include <stdlib.h>
#include <stdio.h>

int ten_to_hex(char * result, int number) {
    int index = 32;
    char x;
    int r = 0;
    while (number != 0) {
        r = number % 16;
        if (r <= 9) {
            result[index] = r + '0';
        }
        else {
            result[index] = (r - 10) + 'A'; 
        }

        index--;
        number /= 16;
    }
    return ++index;
}