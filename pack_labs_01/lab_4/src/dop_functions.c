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
    int * numbers = malloc(sizeof(int) * count);

    for (int i = 0; i < count; ++i) {
        numbers[i] = 0;
    }

    int index = 0;
    for (int i = 2; i < count; ++i) {
        if (numbers[i]) {
            continue;
        }
        for (int j = i + i; j < count; j += i) {
            numbers[j] = 1;
        }
    }
    return numbers;
}