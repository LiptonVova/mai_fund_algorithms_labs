#include "../include/functions.h"
#include <unity.h>


void setUp(void) {

}

void tearDown(void) {

}


void test_strncmp_1(void) {
    const char* str1 = "Hello, World!";
    const char* str2 = "Hello, World!";
    
    int result = strncmp(str1, str2, 13);
    
    TEST_ASSERT_EQUAL(0, result);
}

void test_strncmp_2(void) {
    const char* str1 = "Hello, World!";
    const char* str2 = "Hello, Universe!";
    
    int result = strncmp(str1, str2, 5); // Сравниваем только "Hello"
    
    TEST_ASSERT_EQUAL(0, result);
}
void test_strncmp_3(void) {
    const char* str1 = "Apple";
    const char* str2 = "Banana";
    
    int result = strncmp(str1, str2, 5);
    
    TEST_ASSERT_EQUAL(-1, result);
}
void test_strncmp_4(void) {
    const char* str1 = "Cat";
    const char* str2 = "Bat";
    
    int result = strncmp(str1, str2, 3);
    
    TEST_ASSERT_EQUAL(1, result);
}
void test_strncmp_5(void) {
    const char* str1 = "Hello";
    const char* str2 = "World";
    
    int result = strncmp(str1, str2, 0);
    
    TEST_ASSERT_EQUAL(0, result);
}
void test_strncmp_6(void) {
    const char* str1 = "Hi";
    const char* str2 = "Hello";
    
    int result = strncmp(str1, str2, 5);
    
    TEST_ASSERT_EQUAL(1, result); 
}
void test_strncmp_7(void) {
    const char* str1 = "";
    const char* str2 = "Hello";
    
    int result = strncmp(str1, str2, 5);
    
    TEST_ASSERT_EQUAL(-1, result);
}


int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_strncmp_1);
    RUN_TEST(test_strncmp_2);
    RUN_TEST(test_strncmp_3);
    RUN_TEST(test_strncmp_4);
    RUN_TEST(test_strncmp_5);
    RUN_TEST(test_strncmp_6);
    RUN_TEST(test_strncmp_7);


    return UNITY_END();
}