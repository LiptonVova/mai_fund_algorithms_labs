#include "../include/lab_2.h"
#include <stdlib.h>


void generate_prime_numbers(int * result, int n, int max_number) {
    int * numbers = malloc(sizeof(int) * (n + 1));

    for (int i = 0; i < (n + 1); ++i) {
        numbers[i] = 0;
    }

    int index = 0;
    for (int i = 2; i <= n; ++i) {
        if (numbers[i]) {
            continue;
        }
        result[index] = i;
        index++;
        if (index > max_number) {
            break;
        }
        
        for (int j = i + i; j <= n; j += i) {
            numbers[j] = 1;
        }
    }
    free(numbers);
}