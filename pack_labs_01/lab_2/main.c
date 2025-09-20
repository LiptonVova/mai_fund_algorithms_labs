#include <stdio.h>
#include <stdlib.h>
#include "include/lab_2.h"

typedef enum {
    ERROR_BIG_NUMBER,
} STATUS_CODES;

int main() {
    int T;
    scanf("%d", &T);

    int * input = malloc(sizeof(int) * T);
    int max_number = -1;
    for (int i = 0; i < T; ++i) {
        scanf("%d", &input[i]);
        if (input[i] > max_number) {
            max_number = input[i];
        }
    }

    const int MAX_NUMBER = 1e6;

    if (max_number > MAX_NUMBER) {
        printf("Моя программа поддерживает с порядковым номером до 1e6\n");
        return ERROR_BIG_NUMBER;
    }

    int * result = malloc(sizeof(int) * (max_number + 1));
    int n = max_number * 100;
    generate_prime_numbers(result, n, max_number);

    for (int i = 0; i < T; ++i) {
        printf("простое число под номером %d соответствует числу %d\n", input[i], result[input[i] - 1]);
    }
    free(result);
    free(input);


    return 0;
}