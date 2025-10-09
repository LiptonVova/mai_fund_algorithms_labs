#include <stdio.h>
#include "include/overscanf.h"


int main() {
    int a = 0;
    int b = 0;
    char buffer[] = "::VI%:%k::VI:";
    int result = oversscanf(buffer, "::%Ro%:%k::%Ro:", &a, &b);
    printf("Проверка oversscanf\n");
    printf("a: %d, b: %d, result: %d\n", a, b, result);

    // нужно создать файл test.txt
    // со следующим содержимым: '::vovXX:::/qwerty::101011....   m'
    FILE* file = fopen("test.txt", "r");
    if (!file) {
        printf("Ошибка открытия файла!\n");
        return -1;
    } 
    result = overfscanf(file, "::vov%Ro:::/qwerty::%Zr....   m", &a, &b);
    printf("Проверка overfscanf\n");
    printf("a: %d, b: %d, result: %d\n", a, b, result);
}