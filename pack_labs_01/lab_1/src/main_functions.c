#include "../include/main_functions.h"
#include <stdio.h>

void print_usage() {
    printf("./main.out [number] [flag]\n\n");
    printf("flags and arguments: \n");
    printf("flag -h or /h: выводится в консоль натуральные числа в пределах 100, кратные number\n");
    printf("flag -p or /p: определить простое ли число\n");
    printf("flag -s or /s: перевести число в 16 с/c\n");
    printf("flag -e or /e: вывести таблицу степеней. X не более 10\n");
    printf("flag -a or /a: вычислить сумму от 1 до x\n");
    printf("flag -f or /f: вычислить факториал x, x - неотрицательное\n");
}


int h_flag(int* result, const int number) {
    int index = 0;
    for (int i = 1; i <= 100; ++i) {
        if (i % number == 0) {
            result[index++] = i;
        }
    }
    return index;
}


int p_flag(const int number) {
    for (int i = 2; i * i <= number; ++i) {
        if (number % i == 0) {
            return 0;
        }
    }
    return 1;
}


int s_flag(char* result, const int number) {
    int copy_number = number;

    int index = 32;

    int r;
    while (copy_number != 0) {
        r = copy_number % 16;
        if (r > 9) {
            result[index] = (r - 10) + 'A';
        }
        else {
            result[index] = r + '0'; 
        }
        index--;
        copy_number /= 16;
    }    
    return ++index;
}


void e_flag(long long** result, const int number) {
    long long temp;
    for (long long i = 0; i < 10; ++i) {
        temp = 1;
        for (int j = 0; j < number; ++j) {
            temp *= (i + 1);
            result[i][j] = temp;
        }
    }
}


long long a_flag(const int number) {
    long long result = 0;
    for (int i = 1; i <= number; ++i) {
        result += i;
    }
    return result;
}

long long f_flag(const int number) {
    if (number <= 1) {
        return number;
    }
    long long result = 1;
    for (long long i = 2; i <= number; ++i) {
        result *= i;
    }
    return result;    
}


