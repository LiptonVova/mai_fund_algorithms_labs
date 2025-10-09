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
    print_test_header("Тест базовой функциональности всех спецификаторов");
    
    int roman_val, custom_val_lower, custom_val_upper;
    unsigned int zeck_val;
    const char *input = "XIV:101001:1a:1A";
    
    int base1 = 16;
    int base2 = 16;
    int result = oversscanf(input, "%Ro:%Zr:%Cv:%CV", &roman_val, &zeck_val, &custom_val_lower, base1, &custom_val_upper, base2);
    
    char actual_output[100], expected_output[100];
    snprintf(actual_output, sizeof(actual_output), "%d %u %d %d", roman_val, zeck_val, custom_val_lower, custom_val_upper);
    snprintf(expected_output, sizeof(expected_output), "%d %u %d %d", 14, 3, 26, 26);
    
    printf("result: %d\n", result);
    print_io_info(input, expected_output, actual_output, 4, result);
    test_verdict(result == 4 && roman_val == 14 && zeck_val == 3 && custom_val_lower == 26 && custom_val_upper == 26);
}


void test_2(void) {
    print_test_header("Тест невалидных римских чисел");
    
    int value1 = 0, value2 = 0, value3 = 0;
    const char *input = "MMMM IVI PA";
    
    int result = oversscanf(input, "%Ro %Ro %Ro", &value1, &value2, &value3);
    
    char actual_output[100], expected_output[100];
    snprintf(actual_output, sizeof(actual_output), "%d %d %d", value1, value2, value3);
    snprintf(expected_output, sizeof(expected_output), "%d %d %d", 0, 0, 0);
    
    printf("result: %d\n", result);
    print_io_info(input, expected_output, actual_output, 0, result);
    test_verdict(result == 0);
}


void test_3(void) {
    print_test_header("Тест цекендорфова представления с двумя подряд единицами");
    
    unsigned int value1 = 0;
    const char *input = "11001";
    
    int result = oversscanf(input, "%Zr", &value1);
    
    char actual_output[100], expected_output[100];
    snprintf(actual_output, sizeof(actual_output), "%u", value1);
    snprintf(expected_output, sizeof(expected_output), "%u", 0); 
    
    printf("result: %d\n", result);
    print_io_info(input, expected_output, actual_output, 0, result);
    test_verdict(result == 0);
}


void test_4(void) {
    print_test_header("Тест невалидных значений для Cv и CV");
    
    int value1 = 0, value2 = 0, value3 = 0, value4 = 0;
    const char *input = "1Z 2@ G5 H8";
    
    int base1 = 16;
    int base2 = 10;
    int base3 = 16;
    int base4 = 10;
    int result = oversscanf(input, "%Cv %Cv %CV %CV", &value1, base1, &value2, base2, &value3, base3, &value4, base4);
    
    char actual_output[100], expected_output[100];
    snprintf(actual_output, sizeof(actual_output), "%d %d %d %d", value1, value2, value3, value4);
    snprintf(expected_output, sizeof(expected_output), "%d %d %d %d", 0, 0, 0, 0);
    
    printf("result: %d\n", result);
    print_io_info(input, expected_output, actual_output, 0, result);
    test_verdict(result == 0); 
}


int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_1);
    RUN_TEST(test_2);
    RUN_TEST(test_3);
    RUN_TEST(test_4);

    return UNITY_END();
}