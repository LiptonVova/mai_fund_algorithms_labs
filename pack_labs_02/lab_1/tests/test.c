#include "../include/check_finite_fraction.h"
#include <unity.h>

void setUp(void) {
    // Этот метод вызывается перед каждым тестом
}

void tearDown(void) {
    // Этот метод вызывается после каждого теста
}


void test_1(void) {
    error_code_t error = SUCCESS;
    
    int n = 5;
    double list[] = {0.5, 0.25, 0.125, 0.75, 0.375}; // конечные в двоичной
    int number_system = 2;
    
    bool* result = define_list_of_finite_fraction(number_system, &error, n, 
                                                 list[0], list[1], list[2], list[3], list[4]);
    
    TEST_ASSERT_EQUAL(SUCCESS, error);
    TEST_ASSERT_NOT_NULL(result);

    for (int i = 0; i < n; i++) {
        TEST_ASSERT_TRUE(result[i]);
    }
    
    free(result);
}

void test_2(void) {
    error_code_t error = SUCCESS;
    
    int n = 3;
    double list[] = {0.1, 0.3, 0.7}; // бесконечные в двоичной
    int number_system = 2;
    
    bool* result = define_list_of_finite_fraction(number_system, &error, n, 
                                                 list[0], list[1], list[2]);
    
    TEST_ASSERT_EQUAL(SUCCESS, error);
    TEST_ASSERT_NOT_NULL(result);
    
    for (int i = 0; i < n; i++) {
        TEST_ASSERT_FALSE(result[i]);
    }
    
    free(result);
}

void test_3(void) {
    error_code_t error = SUCCESS;
    
    int n = 3;
    double list[] = {0.125, 0.015625, 0.5}; 
    int number_system = 8;
    
    bool* result = define_list_of_finite_fraction(number_system, &error, n, 
                                                 list[0], list[1], list[2]);
    
    TEST_ASSERT_EQUAL(SUCCESS, error);
    TEST_ASSERT_NOT_NULL(result);
    
    for (int i = 0; i < n; i++) {
        TEST_ASSERT_TRUE(result[i]);
    }
    
    free(result);
}

void test_4(void) {
    error_code_t error = SUCCESS;
    
    int n = 2;
    double list[] = {0.0000, 0, -0.000000}; 
    int number_system = 8;
    
    bool* result = define_list_of_finite_fraction(number_system, &error, n, 
                                                 list[0], list[1], list[2]);
    
    TEST_ASSERT_EQUAL(SUCCESS, error);
    TEST_ASSERT_NOT_NULL(result);
    
    for (int i = 0; i < n; i++) {
        TEST_ASSERT_TRUE(result[i]);
    }
    
    free(result);
}





int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_1);
    RUN_TEST(test_2);
    RUN_TEST(test_3);
    RUN_TEST(test_4);

    return UNITY_END();
}