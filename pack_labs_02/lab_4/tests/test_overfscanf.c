#include "unity.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/overscanf.h"

void print_test_header(const char* test_name) {
    printf("\n=== %s ===\n", test_name);
}

void print_io_info(const char* input, const char* expected_output, const char* actual_output, int expected_result, int actual_result) {
    printf("Ввод: %s\n", input);
    printf("Ожидаемый вывод: %s\n", expected_output);
    printf("Вывод: %s\n", actual_output);
    printf("Ожидаемый результат: %d\n", expected_result);
    printf("Фактический результат: %d\n", actual_result);
}

void test_verdict(int condition) {
    if (condition) {
        printf("Вердикт: ТЕСТ ПРОЙДЕН\n");
    } else {
        printf("Вердикт: ТЕСТ ПРОВАЛЕН\n");
    }
}

void setUp(void) {

}

void tearDown(void) {

}

void test_1(void) {
    int roman_val = 0, custom_val_lower = 0, custom_val_upper = 0;  
    unsigned int zeck_val;
    
    // Создаем временный файл с тестовыми данными
    const char *test_data = "XIV 101001 1a 1A";
    FILE *test_file = fopen("test.txt", "w+");
    if (test_file == NULL) {
        printf("Ошибка создания тестового файла\n");
        TEST_FAIL();
        return;
    }
    
    // Записываем тестовые данные в файл
    fprintf(test_file, "%s", test_data);
    rewind(test_file); // Возвращаемся в начало файла для чтения
    
    int base1 = 16;
    int base2 = 16;
    int result = overfscanf(test_file, "%Ro %Zr %Cv %CV", &roman_val, &zeck_val, &custom_val_lower, base1, &custom_val_upper, base2);
    
    char actual_output[100], expected_output[100];
    snprintf(actual_output, sizeof(actual_output), "%d %u %d %d", roman_val, zeck_val, custom_val_lower, custom_val_upper);
    snprintf(expected_output, sizeof(expected_output), "%d %u %d %d", 14, 3, 26, 26);
    
    printf("result: %d\n", result);
    print_io_info(test_data, expected_output, actual_output, 4, result);
    test_verdict(result == 4 && roman_val == 14 && zeck_val == 3 && custom_val_lower == 26 && custom_val_upper == 26);
    
    // Закрываем и удаляем временный файл
    fclose(test_file);
    remove("test.txt");
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_1);


    return UNITY_END();
}