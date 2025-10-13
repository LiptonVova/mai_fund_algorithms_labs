#include <stdio.h>
#include "include/functions.h"



int main() {
    // рассматриваю тексты, в которых нет задвоенных символов + нет слов > 80 символов
    char filename_1[1000];
    char filename_2[1000];
    filename_1[0] = '\0';
    filename_2[0] = '\0';

    FILE *file_1 = 0;
    FILE *file_2 = 0;

    if (open_file("Введите имя входного файла", "r", filename_1, &file_1) == ERROR_OPEN_FILE) {
        return ERROR_OPEN_FILE;
    }
    
    if (open_file("Введите имя выходного файла", "w", filename_2, &file_2) == ERROR_OPEN_FILE) {
        fclose(file_1);
        return ERROR_OPEN_FILE;
    }

    solve(file_1, file_2);


    return 0;
}