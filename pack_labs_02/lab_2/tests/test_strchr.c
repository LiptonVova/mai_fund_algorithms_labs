#include "../include/functions.h"
#include <unity.h>


void setUp(void) {

}

void tearDown(void) {

}

void test_strchr_1(void) {
    const char* str = "Hello, World!";
    char target = 'W';
    
    char* result = strchr(str, target);
    
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_PTR(str + 7, result); // 'W' на позиции 7
    TEST_ASSERT_EQUAL('W', *result);
}
void test_strchr_2(void) {
    const char* str = "Hello";
    char target = 'H';
    
    char* result = strchr(str, target);
    
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_PTR(str, result); 
    TEST_ASSERT_EQUAL('H', *result);
}
void test_strchr_3(void) {
    const char* str = "Hello";
    char target = 'o';
    
    char* result = strchr(str, target);
    
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_PTR(str + 4, result);
    TEST_ASSERT_EQUAL('o', *result);
}
void test_strchr_4(void) {
    const char* str = "Hello, World!";
    char target = 'z';
    
    char* result = strchr(str, target);
    
    TEST_ASSERT_NULL(result);
}
void test_strchr_5(void) {
    const char* str = "Hello, World!";
    char target = 'l';
    
    char* result = strchr(str, target);
    
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_PTR(str + 2, result);
    TEST_ASSERT_EQUAL('l', *result);
}
void test_strchr_6(void) {
    const char* str = "Hello World";
    char target = ' ';
    
    char* result = strchr(str, target);
    
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_PTR(str + 5, result);
    TEST_ASSERT_EQUAL(' ', *result);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_strchr_1);
    RUN_TEST(test_strchr_2);
    RUN_TEST(test_strchr_3);
    RUN_TEST(test_strchr_4);
    RUN_TEST(test_strchr_5);
    RUN_TEST(test_strchr_6);

    return UNITY_END();
}