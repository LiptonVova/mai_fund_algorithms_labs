#include "../include/lab_2.h"
#include <stdlib.h>
#include <stdio.h>


int * generate_prime_numbers(int max_number) {
    int n = max_number * 100;
    int * numbers = malloc(sizeof(int) * (n + 1));
    if (!numbers) {
        return NULL;
    }
    int * result = malloc(sizeof(int) * (max_number + 1));
    if (!result) {
        free(numbers);
        return NULL;
    }

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
    return result;
}