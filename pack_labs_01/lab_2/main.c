#include <stdio.h>
#include <stdlib.h>
#include "include/lab_2.h"

enum {
    SUCCESS,
    ERROR_NUMBER,
    ERROR_MALLOC,
    ERROR_BIG_NUMBER,
};

int main() {
    int T;
    printf("Введите количество чисел: ");
    scanf("%d", &T);

    int * input = malloc(sizeof(int) * T);
    int max_number = -1;
    printf("Введите %d чисел: ", T);
    for (int i = 0; i < T; ++i) {
        scanf("%d", &input[i]);
        if (input[i] > max_number) {
            max_number = input[i];
        }
        if (input[i] < 0) {
            printf("Номер не может быть отрицательным\n");
            return ERROR_NUMBER;
        }
    }

    const int MAX_NUMBER = 1e6;

    if (max_number > MAX_NUMBER) {
        printf("Моя программа поддерживает с порядковым номером до 1e6\n");
        return ERROR_BIG_NUMBER;
    }



    int * result = generate_prime_numbers(max_number);
    if (!result) {
        printf("Ошибка при выделении памяти\n");
        return ERROR_MALLOC;
    }

    for (int i = 0; i < T; ++i) {
        printf("простое число под номером %d соответствует числу %d\n", input[i], result[input[i] - 1]);
    }
    free(result);
    free(input);

    return SUCCESS;
}