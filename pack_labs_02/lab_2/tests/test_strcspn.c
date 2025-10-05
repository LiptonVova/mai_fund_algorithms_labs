#include "../include/functions.h"
#include <unity.h>


void setUp(void) {

}

void tearDown(void) {

}

void test_strcspn_1(void) {
    const char* str1 = "apple";
    const char* str2 = "a";
    
    size_t result = strcspn(str1, str2);
    
    TEST_ASSERT_EQUAL(0, result);
}
void test_strcspn_2(void) {
    const char* str1 = "HelloWorld";
    const char* str2 = "o";
    
    size_t result = strcspn(str1, str2);
    
    TEST_ASSERT_EQUAL(4, result);
}
void test_strcspn_3(void) {
    const char* str1 = "123456";
    const char* str2 = "abc";
    
    size_t result = strcspn(str1, str2);
    
    TEST_ASSERT_EQUAL(6, result);
}
void test_strcspn_4(void) {
    const char* str1 = "";
    const char* str2 = "abc";
    
    size_t result = strcspn(str1, str2);
    
    TEST_ASSERT_EQUAL(0, result);
}
void test_strcspn_5(void) {
    const char* str1 = "Hello";
    const char* str2 = "";
    
    size_t result = strcspn(str1, str2);
    
    TEST_ASSERT_EQUAL(5, result);
}
void test_strcspn_6(void) {
    const char* str1 = "";
    const char* str2 = "";
    
    size_t result = strcspn(str1, str2);
    
    TEST_ASSERT_EQUAL(0, result);
}



int main() {
    UNITY_BEGIN();

    RUN_TEST(test_strcspn_1);
    RUN_TEST(test_strcspn_2);
    RUN_TEST(test_strcspn_3);
    RUN_TEST(test_strcspn_4);
    RUN_TEST(test_strcspn_5);
    RUN_TEST(test_strcspn_6);


    return UNITY_END();
}