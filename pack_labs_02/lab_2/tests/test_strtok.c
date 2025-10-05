#include "../include/functions.h"
#include <unity.h>



void setUp(void) {

}

void tearDown(void) {

}


void test_strtok_1(void) {
    char str[] = "apple,banana,cherry";
    const char *delim = ",";
    
    char *token = strtok(str, delim);
    TEST_ASSERT_NOT_NULL(token);
    TEST_ASSERT_EQUAL_STRING("apple", token);
    
    token = strtok(NULL, delim);
    TEST_ASSERT_NOT_NULL(token);
    TEST_ASSERT_EQUAL_STRING("banana", token);
    
    token = strtok(NULL, delim);
    TEST_ASSERT_NOT_NULL(token);
    TEST_ASSERT_EQUAL_STRING("cherry", token);
    
    token = strtok(NULL, delim);
    TEST_ASSERT_NULL(token);
}

void test_strtok_2(void) {
    char str[] = "apple,,banana,,,cherry";
    const char *delim = ",";
    
    char *token = strtok(str, delim);
    TEST_ASSERT_EQUAL_STRING("apple", token);
    
    token = strtok(NULL, delim);
    TEST_ASSERT_EQUAL_STRING("banana", token);
    
    token = strtok(NULL, delim);
    TEST_ASSERT_EQUAL_STRING("cherry", token);
    
    token = strtok(NULL, delim);
    TEST_ASSERT_NULL(token);
}

void test_strtok_3(void) {
    char str[] = "apple;banana,cherry:grape";
    const char *delim = ";,:";
    
    char *token = strtok(str, delim);
    TEST_ASSERT_EQUAL_STRING("apple", token);
    
    token = strtok(NULL, delim);
    TEST_ASSERT_EQUAL_STRING("banana", token);
    
    token = strtok(NULL, delim);
    TEST_ASSERT_EQUAL_STRING("cherry", token);
    
    token = strtok(NULL, delim);
    TEST_ASSERT_EQUAL_STRING("grape", token);
    
    token = strtok(NULL, delim);
    TEST_ASSERT_NULL(token);
}

void test_strtok_4(void) {
    char str[] = "  hello   world  test  ";
    const char *delim = " ";
    
    char *token = strtok(str, delim);
    TEST_ASSERT_EQUAL_STRING("hello", token);
    
    token = strtok(NULL, delim);
    TEST_ASSERT_EQUAL_STRING("world", token);
    
    token = strtok(NULL, delim);
    TEST_ASSERT_EQUAL_STRING("test", token);
    
    token = strtok(NULL, delim);
    TEST_ASSERT_NULL(token);
}

void test_strtok_5(void) {
    char str[] = "";
    const char *delim = ",";
    
    char *token = strtok(str, delim);
    TEST_ASSERT_NULL(token);
}

void test_strtok_6(void) {
    char str[] = ",,,,";
    const char *delim = ",";
    
    char *token = strtok(str, delim);
    TEST_ASSERT_NULL(token);
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_strtok_1);
    RUN_TEST(test_strtok_2);
    RUN_TEST(test_strtok_3);
    RUN_TEST(test_strtok_4);
    RUN_TEST(test_strtok_5);
    RUN_TEST(test_strtok_6);

    return UNITY_END();
}