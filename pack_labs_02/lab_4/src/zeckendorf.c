#include "../include/zeckendorf.h"

void generate_fibonacci(unsigned int *result, int count) {
    result[0] = 1;
    result[1] = 1;
    for (int i = 2; i < count; ++i) {
        result[i] = result[i - 1] + result[i - 2];
    }
}

bool validate_zeckendorf(error_code_t *error, const char c, const int prev_value) {
    if (c != '0' && c != '1') {
        *error = ERROR_ZECKENDORF;
        return false;
    }

    if (c == '1' && prev_value == 1) {
        *error = ERROR_ZECKENDORF;
        return false;
    }

    return true;
}

void handle_zeckendorf(error_code_t *error, char* buffer, va_list args) {
    unsigned int answer = 0;

    unsigned int fibonacci[100];
    int n = strlen(buffer);
    int prev_value = 0;
    generate_fibonacci(fibonacci, n);

    for (int i = 0; i < n - 1; ++i) {

        bool validate = validate_zeckendorf(error, buffer[i], prev_value);
        if (!validate) {
            return;
        }

        prev_value = (buffer[i] - '0');
        answer += fibonacci[i] * (buffer[i] - '0'); 
    }
    if (buffer[n - 1] != '1') {
        *error = ERROR_ZECKENDORF;
        return;
    }


    unsigned int* ptr = va_arg(args, unsigned int*);
    *ptr = answer;
}