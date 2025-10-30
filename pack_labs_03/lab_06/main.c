#include <stdio.h>
#include "include/solve.h"


int main() {
    const char buffer[1000];
    printf("Введите строчку, которую надо првоерить на вложенность скобок:\n");
    scanf("%s", buffer);

    int result = check_brackets(buffer);
    if (result) {
        printf("Скобки вложены правильно, ошибок нет!\n");
    }
    else {
        printf("Скобки вложены неправильно, есть ошибки!\n");
    }

    return 0;
}