#include "include/solve.h"
#include <stdio.h>


int main() {
    const int BUF_SIZE = 50;
    char result[BUF_SIZE];
    
    printf("1. Тест с нулем\n");
    translate_to_base(0, 2, result);
    printf("входные данные: number=0, r=2\n");
    printf("ожидаемые выходные данные: 0\n");
    printf("что вывела программа: %s\n", result);
    printf("вердикт: %s\n\n", strcmp(result, "0") == 0 ? "PASS" : "FAIL");
    
    printf("2. Тест с основанием 2\n");
    translate_to_base(5, 1, result);
    printf("входные данные: number=5, r=1\n");
    printf("ожидаемые выходные данные: 101\n");
    printf("что вывела программа: %s\n", result);
    printf("вердикт: %s\n\n", strcmp(result, "101") == 0 ? "PASS" : "FAIL");
    
    printf("3. Тест с основанием 4\n");
    translate_to_base(10, 2, result);
    printf("входные данные: number=10, r=2\n");
    printf("ожидаемые выходные данные: 22\n");
    printf("что вывела программа: %s\n", result);
    printf("вердикт: %s\n\n", strcmp(result, "22") == 0 ? "PASS" : "FAIL");
    
    printf("4. Тест с основанием 8\n");
    translate_to_base(15, 3, result);
    printf("входные данные: number=15, r=3\n");
    printf("ожидаемые выходные данные: 17\n");
    printf("что вывела программа: %s\n", result);
    printf("вердикт: %s\n\n", strcmp(result, "17") == 0 ? "PASS" : "FAIL");
    
    printf("5. Тест с основанием 16\n");
    translate_to_base(27, 4, result);
    printf("входные данные: number=27, r=4\n");
    printf("ожидаемые выходные данные: 1B\n");
    printf("что вывела программа: %s\n", result);
    printf("вердикт: %s\n\n", strcmp(result, "1B") == 0 ? "PASS" : "FAIL");
    
    printf("6. Тест с основанием 32\n");
    translate_to_base(42, 5, result);
    printf("входные данные: number=42, r=32\n");
    printf("ожидаемые выходные данные: 1A\n");
    printf("что вывела программа: %s\n", result);
    printf("вердикт: %s\n\n", strcmp(result, "1A") == 0 ? "PASS" : "FAIL");
    
    printf("7. Тест с большим числом\n");
    translate_to_base(255, 2, result);
    printf("входные данные: number=255, r=2\n");
    printf("ожидаемые выходные данные: 3333\n");
    printf("что вывела программа: %s\n", result);
    printf("вердикт: %s\n\n", strcmp(result, "3333") == 0 ? "PASS" : "FAIL");
    
    printf("8. Тест с граничным значением\n");
    translate_to_base(1, 2, result);
    printf("входные данные: number=1, r=2\n");
    printf("ожидаемые выходные данные: 1\n");
    printf("что вывела программа: %s\n", result);
    printf("вердикт: %s\n\n", strcmp(result, "1") == 0 ? "PASS" : "FAIL");
    
    printf("9. Тест с основанием 4 для числа 7\n");
    translate_to_base(7, 2, result);
    printf("входные данные: number=7, r=2\n");
    printf("ожидаемые выходные данные: 13\n");
    printf("что вывела программа: %s\n", result);
    printf("вердикт: %s\n\n", strcmp(result, "13") == 0 ? "PASS" : "FAIL");
    
    printf("10. Тест отрицательных чисел\n");
    translate_to_base(-5, 3, result);
    printf("входные данные: number=-5, r=3\n");
    printf("ожидаемые выходные данные: -5\n");
    printf("что вывела программа: %s\n", result);
    printf("вердикт: %s\n\n", strcmp(result, "-5") == 0 ? "PASS" : "FAIL");
    
    printf("11. Тест отрицательных чисел\n");
    translate_to_base(-20, 4, result);
    printf("входные данные: number=-20, r=4\n");
    printf("ожидаемые выходные данные: -14\n");
    printf("что вывела программа: %s\n", result);
    printf("вердикт: %s\n", strcmp(result, "-14") == 0 ? "PASS" : "FAIL");
    
    return 0;
}