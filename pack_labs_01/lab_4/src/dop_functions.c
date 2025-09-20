#include "../include/dop_functions.h"
#include <stdlib.h>


double factorial(int n) {
    double result = 1.0;
    for (int i = 1; i <= n; ++i) {
        result *= i;
    }

    return result;
}

int * prime_numbers(int count) {
    int * result = malloc(sizeof(int)*count);
    int SIZE = count * 100;
    int * numbers = malloc(sizeof(int)*SIZE);

    for (int i = 0; i < SIZE; ++i) {
        numbers[i] = 0;
    }

    int index = 0;
    for (int i = 2; i < SIZE; ++i) {
        if (numbers[i]) {
            continue;
        }
        result[index++] = i;
        if (index == count) {
            break;
        }
        for (int j = i; j < SIZE; j += i) {
            numbers[j] = 1;
        }
    }
    free(numbers);
    return result;
}