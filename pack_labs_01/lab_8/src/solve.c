#include "../include/solve.h"
#include <stdlib.h>

int perevod_base_to_ten_cc(char* number, int length, int base) { // перевод из base в десятичную c/c
    int result = 0;
    char c;
    int r;
    char ascii_base;
    char ascii_base_upper;
    if (base < 10) {
        ascii_base = (base + '0');
    }
    else {
        ascii_base_upper = (base - 10) + 'A';
        ascii_base = (base - 10) + 'a';
    }
    for (int i = 0; i < length; ++i) {
        c = number[i];
        if (c >= '0' && c <= '9' && c < ascii_base) {
            r = (c - '0');  
        }
        else if (c >= 'a' && c <= 'z' && c < ascii_base) {
            r = (c - 'a') + 10;
        }
        else if (c >= 'A' && c <= 'Z' && c < ascii_base_upper) {
            r = (c - 'A') + 10;
        }
        else {
            return -1;
        }

        result = result * base + r;
    }
    return result;
}

void reverse(char * result, int length) {
    char temp;
    for (int i = 0; i < length/2; ++i) {
        temp = result[i]; 
        result[i] = result[length - i - 1];
        result[length - i - 1] = temp;
    }
}

char* perevod_ten_cc_to_base(const int number, int base) {
    char* result = malloc(sizeof(char) * 34);
    int index = 0;

    int r;
    int copy_number = number;
    while (copy_number != 0) {
        r = copy_number % base;
        if (r > 9) {
            result[index++] = (r - 10) + 'A';
        }
        else {
            result[index++] = r + '0';            
        }
        copy_number /= base;
    }

    reverse(result, index);
    result[index] = '\0';
    return result;
}