#include "../include/additional_functions.h"

void int_to_roman(int num, char* buffer) {
    const char* roman_literals[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    const int roman_values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};

    if (num <= 0 || num > 3999) {
        strcpy(buffer, "NaN");
        return;
    }

    buffer[0] = '\0';
    int i = 0;
    while (num > 0) {
        while (num >= roman_values[i]) {
            strcat(buffer, roman_literals[i]);
            num -= roman_values[i];
        }
        ++i;
    }
}

void generate_fibonacci(const unsigned int num, unsigned int* fib, int* count) {
    fib[0] = 1;
    if (num == 1) {
        *count = 1;
        return;    
    }
    fib[1] = 1;
    int index = 2;
    while (fib[index - 1] < num) {
        fib[index] = fib[index - 1] + fib[index - 2];
        ++index;
    }
    *count = index - 1;
}

void zeckendorf(const unsigned int num, char* buffer) {
    if (num == 0) {
        strcpy(buffer, "1");
        return ;
    }

    unsigned int fib[1000];
    int count = 0;
    generate_fibonacci(num, fib, &count);
    unsigned int remaining = num;

    char* coefficients[1000];    

    if (fib[count] != num) {
        --count;
    }

    for (int i = count; i >= 0; --i) {
        if (remaining >= fib[i]) {
            coefficients[i] = "1";
            remaining -= fib[i];
        }
        else {
            coefficients[i] = "0";
        }
    }
    buffer[0] = '\0';
    for (int i = 0; i <= count; ++i) {
        strcat(buffer, coefficients[i]);
    }
    strcat(buffer, "1"); // заверщающая единица
}

void translate_ten_to_base_cc_impl(int num, const int base, char* buffer, const char letter, int*index) {
    int r = 0;

    while (num != 0) {
        r = num % base;
        if (r > 9) {
            buffer[*index] = (r - 10) + letter;
        }
        else {
            buffer[*index] = r + '0';
        }
        num /= base;
        (*index)++;
    }
}

void translate_ten_to_base_cc(const int num, const int base, char* buffer, bool upper) {
    char temp[1000];
    int copy_num = num;
    if (base < 2 || base > 36) {
        sprintf(buffer, "%d", num);
        return;
    }
    char letter = 'a';
    if (upper) {
        letter = 'A';
    }
    int index = 0;

    translate_ten_to_base_cc_impl(copy_num, base, temp, letter, &index);

    int i = 0;
    for ( ; i < index; ++i) {
        buffer[i] = temp[index - i - 1]; 
    }
    buffer[index] = '\0';
}

void translate_base_to_ten_cc_impl(const char * num, const int base, int* result, const char letter_a, const char letter_z) {
    char c = '\0';
    int r = 0;
    while (*num != '\0') {
        c = *num;
        if (c >= '0' && c <= '9') {
            r = c - '0';
        }
        else if (c >= letter_a && c <= letter_z) {
            r = c - letter_a + 10;
        }
        else {
            result = NULL;
            return;
        }

        if (r >= base) {
            result = NULL;
            return;
        }

        *result = (*result) * base + r;
        ++num;
    }
}

int* translate_base_to_ten_cc(const char*num, const int base, int* result, bool upper) {
    int copy_base = base;
    if (base < 2 || base > 36) {
        copy_base = 10;
    }

    bool negative = false;
    if (*num == '-') {
        negative = true;
        ++num;
    }

    char letter_a = 'a';
    char letter_z = 'z';
    if (upper) {
        letter_a = 'A';
        letter_z = 'Z';
    }

    translate_base_to_ten_cc_impl(num, copy_base, result, letter_a, letter_z);
    if (result == NULL) {
        return NULL;
    }

    if (negative) {
        *result *= -1;
    }
    return result;
}

void define_size(int* size, const char type) {
    if (type == 'i') {
        *size = sizeof(int);
    } 
    else if (type == 'u') {
        *size = sizeof(unsigned int);
    }

    else if (type == 'd') {
        *size = sizeof(double);
    }

    else if (type == 'f') {
        *size = sizeof(float);
    }
}


void memory_dump(error_code_t *error, const unsigned char*bytes, unsigned char* buffer, const char type) {
    int index = 0;
    int size = 0;

    define_size(&size, type);
    if (size == 0) {
        *error = ERROR_UNKNOWN_MEMORY_TYPE;
        return;
    }

    for (int i = 0; i < size; ++i) {

        for (int j = 7; j >= 0; --j) {
            buffer[index++] = (bytes[i] & (1 << j)) ? '1' : '0';
        }

        if (i < size - 1) {
            buffer[index++] = ' ';
        }
    }
    buffer[index] = '\0';
}